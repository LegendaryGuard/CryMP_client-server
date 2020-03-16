/**
 * @file
 * @brief Implementation of CryMP client telemetry services.
 */

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Library/PicoSHA2.h"

#include "Telemetry.h"
#include "Log.h"

static std::string GetMachineGUID()
{
	const char *keyName = "SOFTWARE\\Microsoft\\Cryptography";
	const char *valueName = "MachineGuid";

	HKEY key;
	if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, keyName, 0, KEY_QUERY_VALUE | KEY_WOW64_64KEY, &key))
	{
		return std::string();
	}

	char buffer[256];
	DWORD length = static_cast<DWORD>(sizeof buffer);
	if (RegQueryValueExA(key, valueName, NULL, NULL, reinterpret_cast<LPBYTE>(buffer), &length) || length == 0)
	{
		return std::string();
	}

	length--;  // skip terminating null character

	return std::string(buffer, length);
}

bool Telemetry::init()
{
	std::string machineGUID = GetMachineGUID();
	if (!machineGUID.empty())
	{
		// use SHA-256 hash of machine GUID as HWID
		m_hwid = picosha2::hash256_hex_string(machineGUID);
	}
	else
	{
		LogError("Telemetry: Failed to get machine GUID - error code %lu", GetLastError());
		m_hwid.clear();
	}

	char localeNameBuffer[LOCALE_NAME_MAX_LENGTH];
	if (GetLocaleInfoA(LOCALE_USER_DEFAULT, LOCALE_SNAME, localeNameBuffer, LOCALE_NAME_MAX_LENGTH))
	{
		m_locale = localeNameBuffer;
	}
	else
	{
		LogError("Telemetry: Failed to get locale information - error code %lu", GetLastError());
		m_locale.clear();
	}

	TIME_ZONE_INFORMATION tz;
	if (GetTimeZoneInformation(&tz) != TIME_ZONE_ID_INVALID)
	{
		m_tzBias = tz.Bias;
	}
	else
	{
		LogError("Telemetry: Failed to get time zone information - error code %lu", GetLastError());
		m_tzBias = 0;
	}

	return true;
}

std::string Telemetry::generateUUID(const char *salt) const
{
	if (!salt)
	{
		salt = "idsvc";
	}

	if (getHWID().empty())
	{
		return std::string();
	}

	return getHWID() + ':' + picosha2::hash256_hex_string(getHWID() + salt);
}