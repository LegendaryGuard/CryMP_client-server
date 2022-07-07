#include <windows.h>
#include <malloc.h>  // _msize
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <mutex>

#include "CryCommon/CrySystem/ISystem.h"
#include "CryCommon/CrySystem/IConsole.h"

#include "Library/DLL.h"
#include "Library/Format.h"
#include "Library/WinAPI.h"

#include "CryMemoryManager.h"

namespace
{
	struct DebugAllocatorMetadata
	{
		void* address = nullptr;
		size_t requestedSize = 0;
		size_t totalSize = 0;
		std::string callstack;
	};

	struct DebugAllocator
	{
		std::vector<void*> blocks;
		std::vector<DebugAllocatorMetadata> metadata;
		std::mutex mutex;
		size_t pageSize = 0;
		int enabled = 0;
		unsigned int mainThreadID = 0;

		DebugAllocator()
		{
			SYSTEM_INFO info = {};
			GetSystemInfo(&info);

			pageSize = info.dwPageSize;
			mainThreadID = GetCurrentThreadId();
		}
	};

	DebugAllocator g_allocator;

	std::string CaptureCallstack()
	{
		constexpr unsigned int MAX_COUNT = 60;

		void* buffer[MAX_COUNT];
		const unsigned int count = RtlCaptureStackBackTrace(0, MAX_COUNT, buffer, nullptr);

		std::string result;

		for (unsigned int i = 0; i < count; i++)
		{
			result += Format("%p\r\n", buffer[i]);
		}

		return result;
	}

	void* Allocate(size_t size)
	{
		if (!g_allocator.enabled || GetCurrentThreadId() == g_allocator.mainThreadID)
		{
			return malloc(size);
		}

		const size_t blockPageCount = (size + g_allocator.pageSize - 1) / g_allocator.pageSize;
		const size_t totalSize = (2 + blockPageCount) * g_allocator.pageSize;

		void* address = VirtualAlloc(nullptr, totalSize, MEM_COMMIT, PAGE_NOACCESS);
		if (!address)
		{
			return nullptr;
		}

		void* block = static_cast<uint8_t*>(address) + g_allocator.pageSize;

		DWORD _;
		VirtualProtect(block, size, PAGE_READWRITE, &_);

		memset(block, 0, blockPageCount * g_allocator.pageSize);

		std::string callstack = CaptureCallstack();

		std::lock_guard lock(g_allocator.mutex);

		const size_t remainingSize = size % g_allocator.pageSize;
		const size_t blockAlignment = (remainingSize > 0) ? g_allocator.pageSize - remainingSize : 0;
		block = static_cast<uint8_t*>(block) + blockAlignment;

		g_allocator.blocks.emplace_back(block);
		g_allocator.metadata.emplace_back();
		g_allocator.metadata.back().address = address;
		g_allocator.metadata.back().requestedSize = size;
		g_allocator.metadata.back().totalSize = totalSize;
		g_allocator.metadata.back().callstack = std::move(callstack);

		printf("%04x: Allocate(%zu) -> %p\n", GetCurrentThreadId(), size, block);

		return block;
	}

	size_t Deallocate(void* block)
	{
		{
			std::lock_guard lock(g_allocator.mutex);

			for (size_t i = 0; i < g_allocator.blocks.size(); i++)
			{
				if (g_allocator.blocks[i] == block)
				{
					const size_t size = g_allocator.metadata[i].requestedSize;

					VirtualFree(g_allocator.metadata[i].address, 0, MEM_RELEASE);

					g_allocator.blocks.erase(g_allocator.blocks.begin() + i);
					g_allocator.metadata.erase(g_allocator.metadata.begin() + i);

					printf("%04x: Deallocate(%p) -> %zu\n", GetCurrentThreadId(), block, size);

					return size;
				}
			}
		}

		// fallback
		const size_t size = _msize(block);
		free(block);

		return size;
	}

	size_t GetSize(void* block)
	{
		{
			std::lock_guard lock(g_allocator.mutex);

			for (size_t i = 0; i < g_allocator.blocks.size(); i++)
			{
				if (g_allocator.blocks[i] == block)
				{
					return g_allocator.metadata[i].requestedSize;
				}
			}
		}

		// fallback
		return _msize(block);
	}

	void *CryMalloc_hook(size_t size, size_t & allocatedSize)
	{
		void *result = nullptr;

		if (size)
		{
			result = Allocate(size);
			allocatedSize = size;
		}
		else
		{
			allocatedSize = 0;
		}

		return result;
	}

	void *CryRealloc_hook(void *mem, size_t size, size_t & allocatedSize)
	{
		void *result = nullptr;

		allocatedSize = 0;

		if (size)
		{
			const size_t oldSize = GetSize(mem);

			if (size > oldSize)
			{
				result = Allocate(size);

				if (result)
				{
					memcpy(result, mem, oldSize);
					allocatedSize = size;
				}

				Deallocate(mem);
			}
			else
			{
				result = mem;
				allocatedSize = size;
			}
		}
		else if (mem)
		{
			Deallocate(mem);
		}

		return result;
	}

	size_t CryFree_hook(void *mem)
	{
		size_t size = 0;

		if (mem)
		{
			size = Deallocate(mem);
		}

		return size;
	}

	void *CrySystemCrtMalloc_hook(size_t size)
	{
		void *result = nullptr;

		if (size)
		{
			result = malloc(size);
		}

		return result;
	}

	void CrySystemCrtFree_hook(void *mem)
	{
		if (mem)
		{
			free(mem);
		}
	}

	void Hook(void *pFunc, void *pNewFunc)
	{
		if (!pFunc)
		{
			return;
		}

	#ifdef BUILD_64BIT
		unsigned char code[] = {
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // mov rax, 0x0
			0xFF, 0xE0                                                   // jmp rax
		};

		memcpy(&code[2], &pNewFunc, 8);
	#else
		unsigned char code[] = {
			0xB8, 0x00, 0x00, 0x00, 0x00,  // mov eax, 0x0
			0xFF, 0xE0                     // jmp eax
		};

		memcpy(&code[1], &pNewFunc, 4);
	#endif

		WinAPI::FillMem(pFunc, code, sizeof code);
	}
}

void CryMemoryManager::Init(const DLL & CrySystem)
{
	Hook(CrySystem.GetSymbolAddress("CryMalloc"), CryMalloc_hook);
	Hook(CrySystem.GetSymbolAddress("CryRealloc"), CryRealloc_hook);
	Hook(CrySystem.GetSymbolAddress("CryFree"), CryFree_hook);
	Hook(CrySystem.GetSymbolAddress("CrySystemCrtMalloc"), CrySystemCrtMalloc_hook);
	Hook(CrySystem.GetSymbolAddress("CrySystemCrtFree"), CrySystemCrtFree_hook);

	using WinAPI::RVA;
	using WinAPI::FillNOP;

	void *pCrySystem = CrySystem.GetHandle();

#ifdef BUILD_64BIT
	FillNOP(RVA(pCrySystem, 0x30C3), 0x2);
	FillNOP(RVA(pCrySystem, 0x31A0), 0x2);
#else
	// TODO
#endif
}

void CryMemoryManager::RegisterCVars()
{
	gEnv->pConsole->Register("sys_debugAllocator", &g_allocator.enabled, 0, VF_NOT_NET_SYNCED);
}

std::string CryMemoryManager::GetCallstack(void* address)
{
	std::lock_guard lock(g_allocator.mutex);

	for (const auto& metadata : g_allocator.metadata)
	{
		const void* endAddress = static_cast<const uint8_t*>(metadata.address) + metadata.totalSize;

		if (address >= metadata.address && address < endAddress)
		{
			return metadata.callstack;
		}
	}

	return {};
}
