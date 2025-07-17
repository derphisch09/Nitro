#include "../SDK/SDK.h"

static uintptr_t BaseFileSystem = I::FileSystem + 0x8;

MAKE_HOOK(IBaseFileSystem_Open, U::Memory.GetVirtual(BaseFileSystem, 2), FileHandle_t, void* rcx, const char* pFileName, const char* pOptions, const char* pathID)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::IBaseFileSystem_Open[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, pFileName, pOptions, pathID);
#endif

	if (SDK::BlacklistFile(pFileName))
		return nullptr;

	return CALL_ORIGINAL(rcx, pFileName, pOptions, pathID);
}