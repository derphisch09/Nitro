#include "../SDK/SDK.h"

MAKE_SIGNATURE(CBaseAnimating_EnableAbsRecomputations, "client.dll", "55 8B EC FF 15 ? ? ? ? 0F B6 15 ? ? ? ? 84 C0 0F B6 4D 08 0F 45 D1 88 15 ? ? ? ? 5D C3", 0x0);

MAKE_HOOK(CBaseAnimating_EnableAbsRecomputations, S::CBaseAnimating_EnableAbsRecomputations(), void, void* rcx, bool bEnable)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CBaseAnimating_EnableAbsRecomputations[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, bEnable);
#endif

	return CALL_ORIGINAL(rcx, bEnable);
}