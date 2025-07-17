#include "../SDK/SDK.h"

MAKE_SIGNATURE(CBaseEntity_ToolRecordEntities, "client.dll", "55 8B EC 83 EC 14 8B 0D ? ? ? ? 53 56 33 F6 33 DB 89 5D EC 89 75 F0 8B 41 08 89 75 F4 85 C0 74 3E 68 ? ? ? ? 68 ? ? ? ? 68 ? ? ? ? 68 ? ? ? ? 68 ? ? ? ? 68", 0x0);

MAKE_HOOK(CBaseEntity_ToolRecordEntities, S::CBaseEntity_ToolRecordEntities(), void, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CBaseEntity_ToolRecordEntities[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	return CALL_ORIGINAL(rcx);
}