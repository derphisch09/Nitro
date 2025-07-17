#include "../SDK/SDK.h"

MAKE_HOOK(IFileSystem_FindFirst, U::Memory.GetVirtual(I::FileSystem, 27), const char*, void* rcx, const char* pWildCard, FileFindHandle_t* pHandle)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::IFileSystem_FindFirst[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, handle);
#endif

	auto p = CALL_ORIGINAL(rcx, pWildCard, pHandle);

	while (p && SDK::BlacklistFile(p))
		p = CALL_ORIGINAL(rcx, *pHandle);

	return p;
}