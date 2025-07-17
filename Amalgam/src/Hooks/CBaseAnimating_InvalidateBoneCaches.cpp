#include "../SDK/SDK.h"

MAKE_SIGNATURE(CBaseAnimating_InvalidateBoneCaches, "client.dll", "E8 ? ? ? ? 6A 01 6A 01 8D 4D 0F", 0x0);

MAKE_HOOK(CBaseAnimating_InvalidateBoneCaches, S::CBaseAnimating_InvalidateBoneCaches(), void, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CBaseAnimating_InvalidateBoneCaches[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	return CALL_ORIGINAL(rcx);
}