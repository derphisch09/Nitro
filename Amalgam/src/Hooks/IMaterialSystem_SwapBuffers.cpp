#include "../SDK/SDK.h"

MAKE_HOOK(IMaterialSystem_SwapBuffers, U::Memory.GetVirtual(I::MaterialSystem, 40), void, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::IMaterialSystem_SwapBuffers[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	return;
}