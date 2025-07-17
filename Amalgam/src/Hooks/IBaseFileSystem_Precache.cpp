#include "../SDK/SDK.h"

static uintptr_t BaseFileSystem = I::FileSystem + 0x8;

AKE_HOOK(IBaseFileSystem_Precache, U::Memory.GetVirtual(BaseFileSystem, 9), bool, void* rcx, const char* pFileName, const char* pPathID)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::IBaseFileSystem_Precache[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, pFileName, pOptions, pathID);
#endif

	return true;
}