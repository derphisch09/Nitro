#include "../SDK/SDK.h"

MAKE_SIGNATURE(CBaseEntity_AddVisibleEntities, "client.dll", "55 8B EC 83 EC 18 8B 0D ? ? ? ? 53 33 DB 89 5D E8 89 5D EC 8B 41 08 89 5D F4 89 5D F8 56 57 85 C0 74 41 68 ? ? ? ? 68", 0x0);

MAKE_HOOK(CBaseEntity_AddVisibleEntities, S::CBaseEntity_AddVisibleEntities(), void, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CBaseEntity_AddVisibleEntities[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	return CALL_ORIGINAL(rcx);
}