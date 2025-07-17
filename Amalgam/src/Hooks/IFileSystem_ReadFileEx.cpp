#include "../SDK/SDK.h"

MAKE_HOOK(IFileSystem_ReadFileEx, U::Memory.GetVirtual(I::FileSystem, 71), int, void* rcx, const char* pFileName, const char* pPath, void** ppBuf, bool bNullTerminate, bool bOptimalAlloc, int nMaxBytes, int nStartingByte, FSAllocFunc_t pfnAlloc)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::IFileSystem_ReadFileEx[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, pFileName, pPath, ppBuf, bNullTerminate, bOptimalAlloc, nMaxBytes, nStartingByte, pfnAlloc);
#endif

	if (SDK::BlacklistFile(pFileName))
		return 0;

	return CALL_ORIGINAL(rcx, pFileName, pPath, ppBuf, bNullTerminate, bOptimalAlloc, nMaxBytes, nStartingByte, pfnAlloc);
}