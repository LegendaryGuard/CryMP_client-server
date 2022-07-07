#pragma once

#include <string>

struct DLL;

namespace CryMemoryManager
{
	void Init(const DLL & CrySystem);
	void RegisterCVars();

	std::string GetCallstack(void* address);
}
