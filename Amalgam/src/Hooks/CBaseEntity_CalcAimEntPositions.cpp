#include "../SDK/SDK.h"

MAKE_SIGNATURE(CBaseEntity_CalcAimEntPositions, "client.dll", "55 8B EC 81 EC ? ? ? ? A1 ? ? ? ? 53 33 DB 89 45 D8 89 5D DC 85 C0 0F 8E ? ? ? ? 56 57 A1 ? ? ? ? 8B 1C 98 F6 43 7C 01 0F 84 ? ? ? ? 80 3D ? ? ? ? ? 0F 84", 0x0);

MAKE_HOOK(CBaseEntity_CalcAimEntPositions, S::CBaseEntity_CalcAimEntPositions(), void, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CBaseEntity_CalcAimEntPositions[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	return CALL_ORIGINAL(rcx);
}