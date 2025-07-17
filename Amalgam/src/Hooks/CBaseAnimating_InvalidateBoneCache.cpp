#include "../SDK/SDK.h"

//MAKE_SIGNATURE(CBaseAnimating_InvalidateBoneCache, "client.dll", "55 8B EC A1 ? ? ? ? D9 45 0C 48 56 8B F1 51 D9 1C 24 89 86 ? ? ? ? 8B 06 C7 86 ? ? ? ? ? ? ? ? FF 90 ? ? ? ? D9 45 0C 8D 4E 04 8B 01 51 D9 1C 24 68", 0x0);

MAKE_HOOK(CBaseAnimating_InvalidateBoneCache, S::CBaseAnimating_InvalidateBoneCache(), void, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CBaseAnimating_InvalidateBoneCache[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	return CALL_ORIGINAL(rcx);
}