#include "../SDK/SDK.h"

MAKE_SIGNATURE(CBaseEntity_MoveToLastReceivedPosition, "client.dll", "55 8B EC 80 7D 08 00 56 8B F1 75 0A 80 7E 58 17 0F 84 ? ? ? ? F3 0F 10 86 ? ? ? ? 0F 2E 86 ? ? ? ? 9F F6 C4 44 7A 2A F3 0F 10 86 ? ? ? ? 0F 2E 86 ? ? ? ? 9F F6 C4 44 7A 15 F3", 0x0);

MAKE_HOOK(CBaseEntity_MoveToLastReceivedPosition, S::CBaseEntity_MoveToLastReceivedPosition(), void, void* rcx, bool force)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CBaseEntity_MoveToLastReceivedPosition[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, force);
#endif

	return CALL_ORIGINAL(rcx, force);
}