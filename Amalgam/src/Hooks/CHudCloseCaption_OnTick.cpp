#include "../SDK/SDK.h"

MAKE_SIGNATURE(CHudCloseCaption_OnTick, "client.dll", "55 8B EC 83 EC 08 53 56 57 8B F9 8D 4F D4 E8 ? ? ? ? 80 BF ? ? ? ? ? 8B CF A1 ? ? ? ? 8B 9F ? ? ? ? F3 0F 10 40 ? F3 0F 11 45 ? 74 1F 8B 07 6A 01 FF 90 ? ? ? ? 85 DB 75 29 66 39 9F ? ? ? ? 75 20 88 9F ? ? ? ? EB 18 A1 ? ? ? ? 8B 17 83 78 30 00", 0x0);

MAKE_HOOK(CHudCloseCaption_OnTick, S::CHudCloseCaption_OnTick(), void, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CHudCloseCaption_OnTick[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	return CALL_ORIGINAL(rcx);
}