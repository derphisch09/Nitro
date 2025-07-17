#include "../SDK/SDK.h"

MAKE_SIGNATURE(CBaseAnimating_SetAbsQueriesValid, "client.dll", "55 8B EC FF 15 ? ? ? ? 84 C0 74 0B 80 7D 08 00 0F 95 05 ? ? ? ? 5D C3", 0x0);

MAKE_HOOK(CBaseAnimating_SetAbsQueriesValid, S::CBaseAnimating_SetAbsQueriesValid(), void, void* rcx, bool bValid)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CBaseAnimating_SetAbsQueriesValid[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, bValid);
#endif

	return CALL_ORIGINAL(rcx, bValid;
}