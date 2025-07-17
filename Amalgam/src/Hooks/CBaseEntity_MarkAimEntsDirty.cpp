#include "../SDK/SDK.h"

MAKE_SIGNATURE(CBaseEntity_MarkAimEntsDirty, "client.dll", "8B 15 ? ? ? ? 33 C0 85 D2 7E 25 8D 64 24 00 8B 0D ? ? ? ? 8B 0C 81 F7 41 ? ? ? ? ? 74 0A 81 89 ? ? ? ? ? ? ? ? 40", 0x0);

MAKE_HOOK(CBaseEntity_MarkAimEntsDirty, S::CBaseEntity_MarkAimEntsDirty(), void, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CBaseEntity_MarkAimEntsDirty[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	return CALL_ORIGINAL(rcx);
}