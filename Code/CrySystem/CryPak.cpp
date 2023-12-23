#include "CryPak.h"
#include "Logger.h"

CryPak::CryPak()
{
}

CryPak::~CryPak()
{
}

////////////////////////////////////////////////////////////////////////////////
// ICryPak
////////////////////////////////////////////////////////////////////////////////

const char* CryPak::AdjustFileName(const char* src, char* dst, unsigned int flags, bool* foundInPak)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

bool CryPak::Init(const char* basePath)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

void CryPak::Release()
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
}

bool CryPak::OpenPack(const char* name, unsigned int flags)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

bool CryPak::OpenPack(const char* bindingRoot, const char* name, unsigned int flags)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

bool CryPak::ClosePack(const char* name, unsigned int flags)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

bool CryPak::OpenPacks(const char* wildcard, unsigned int flags)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

bool CryPak::OpenPacks(const char* bindingRoot, const char* wildcard, unsigned int flags)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

bool CryPak::ClosePacks(const char* wildcard, unsigned int flags)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

void CryPak::AddMod(const char* mod)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
}

void CryPak::RemoveMod(const char* mod)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
}

void CryPak::ParseAliases(const char* commandLine)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
}

void CryPak::SetAlias(const char* name, const char* alias, bool add)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
}

const char* CryPak::GetAlias(const char* name, bool returnSame)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

ICryPak::PakInfo* CryPak::GetPakInfo()
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

void CryPak::FreePakInfo(PakInfo* pakInfo)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
}

FILE* CryPak::FOpen(const char* name, const char* mode, unsigned int flags)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

FILE* CryPak::FOpen(const char* name, const char* mode, char* fileGamePath, int length)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

size_t CryPak::FReadRaw(void* data, size_t length, size_t elementCount, FILE* handle)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

size_t CryPak::FReadRawAll(void* data, size_t fileSize, FILE* handle)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

void* CryPak::FGetCachedFileData(FILE* handle, size_t& fileSize)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

size_t CryPak::FWrite(const void* data, size_t length, size_t elementCount, FILE* handle)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

int CryPak::FPrintf(FILE* handle, const char* format, ...)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

char* CryPak::FGets(char* buffer, int bufferSize, FILE* handle)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

int CryPak::Getc(FILE* handle)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

size_t CryPak::FGetSize(FILE* handle)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

int CryPak::Ungetc(int ch, FILE* handle)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

bool CryPak::IsInPak(FILE* handle)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

bool CryPak::RemoveFile(const char* name)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

bool CryPak::RemoveDir(const char* name, bool recurse)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

bool CryPak::IsAbsPath(const char* path)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

size_t CryPak::FSeek(FILE* handle, long seek, int mode)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

long CryPak::FTell(FILE* handle)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

int CryPak::FClose(FILE* handle)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

int CryPak::FEof(FILE* handle)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

int CryPak::FError(FILE* handle)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

int CryPak::FGetErrno()
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

int CryPak::FFlush(FILE* handle)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

void* CryPak::PoolMalloc(size_t size)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

void CryPak::PoolFree(void* pool)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
}

intptr_t CryPak::FindFirst(const char* dir, struct _finddata_t* fd, unsigned int flags)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

int CryPak::FindNext(intptr_t handle, struct _finddata_t* fd)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

int CryPak::FindClose(intptr_t handle)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

ICryPak::FileTime CryPak::GetModificationTime(FILE* handle)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

bool CryPak::IsFileExist(const char* name)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

bool CryPak::MakeDir(const char* path)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

ICryArchive* CryPak::OpenArchive(const char* path, unsigned int flags)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

const char* CryPak::GetFileArchivePath(FILE* handle)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

int CryPak::RawCompress(const void* uncompressed, unsigned long* dstSize, void* compressed, unsigned long srcSize, int level)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

int CryPak::RawUncompress(void* uncompressed, unsigned long* dstSize, const void* compressed, unsigned long srcSize)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

void CryPak::RecordFileOpen(const ERecordFileOpenList list)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
}

void CryPak::RecordFile(FILE* handle, const char* name)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
}

IResourceList* CryPak::GetRecorderdResourceList(const ERecordFileOpenList list)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

ICryPak::ERecordFileOpenList CryPak::GetRecordFileOpenList()
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

void CryPak::Notify(ENotifyEvent event)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
}

std::uint32_t CryPak::ComputeCRC(const char* path)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

bool CryPak::ComputeMD5(const char* path, unsigned char* md5)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

void CryPak::RegisterFileAccessSink(ICryPakFileAcesssSink* pSink)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
}

void CryPak::UnregisterFileAccessSink(ICryPakFileAcesssSink* pSink)
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
}

bool CryPak::GetLvlResStatus() const
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

const char* CryPak::GetModDir() const
{
	CryLogErrorAlways("[" __FUNCTION__ "] NOT IMPLEMENTED!");
	return {};
}

////////////////////////////////////////////////////////////////////////////////
