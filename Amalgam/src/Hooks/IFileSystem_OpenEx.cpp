#include "../SDK/SDK.h"

MAKE_HOOK(IFileSystem_OpenEx, U::Memory.GetVirtual(I::FileSystem, 69), FileHandle_t, void* rcx, const char* pFileName, const char* pOptions, unsigned flags, const char* pathID, char** ppszResolvedFilename)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::IFileSystem_OpenEx[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, pFileName, pOptions, flags, pathID, ppszResolvedFilename);
#endif

	if (pFileName && SDK::BlacklistFile(pFileName))
		return nullptr;

	return CALL_ORIGINAL(rcx, pFileName, pOptions, flags, pathID, ppszResolvedFilename);
}