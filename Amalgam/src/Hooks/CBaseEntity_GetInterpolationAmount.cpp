#include "../SDK/SDK.h"

MAKE_SIGNATURE(CBaseEntity_GetInterpolationAmount, "client.dll", "55 8B EC 51 56 57 8B F1 BF ? ? ? ? E8 ? ? ? ? 84 C0 B9 ? ? ? ? 0F 45 F9 80 BE ? ? ? ? ? 89 7D FC 0F 85 ? ? ? ? 8B 06 8B CE 8B", 0x0);

MAKE_HOOK(CBaseEntity_GetInterpolationAmount, S::CBaseEntity_GetInterpolationAmount(), float, void* rcx, int flags)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CBaseEntity_GetInterpolationAmount[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, flags);
#endif

	return CALL_ORIGINAL(rcx, flags);
}