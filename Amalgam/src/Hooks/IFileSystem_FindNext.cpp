#include "../SDK/SDK.h"

MAKE_HOOK(IFileSystem_FindNext, U::Memory.GetVirtual(I::FileSystem, 28), const char*, void* rcx, FileFindHandle_t handle)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::IFileSystem_FindNext[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, handle);
#endif

	const char* p;

	do
		p = CALL_ORIGINAL(rcx, handle);
	while (p && SDK::BlacklistFile(p));

	return p;
}