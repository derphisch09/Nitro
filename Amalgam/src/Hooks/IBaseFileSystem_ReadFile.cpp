#include "../SDK/SDK.h"

class CUtlBuffer;

static uintptr_t BaseFileSystem = I::FileSystem + 0x8;

MAKE_HOOK(IBaseFileSystem_ReadFile, U::Memory.GetVirtual(BaseFileSystem, 14), bool, void* rcx, const char* pFileName, const char* pPath, CUtlBuffer& buf, int nMaxBytes, int nStartingByte, FSAllocFunc_t pfnAlloc)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::IBaseFileSystem_ReadFile[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, pFileName, pPath, buf, nMaxBytes, nStartingByte, pfnAlloc);
#endif

	if (SDK::BlacklistFile(pFileName))
		return false;

	return CALL_ORIGINAL(rcx, pFileName, pPath, buf, nMaxBytes, nStartingByte, pfnAlloc);
}