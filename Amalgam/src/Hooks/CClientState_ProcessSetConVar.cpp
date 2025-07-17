#include "../SDK/SDK.h"

MAKE_SIGNATURE(CClientState_ProcessSetConVar, "engine.dll", "55 8B EC 8B 49 08 83 EC 0C 8B 01 8B 40 18 FF D0 84 C0 0F 85 ? ? ? ? 8B 45 08 53 33 DB 39 58 20 0F 8E ? ? ? ? 33 C9 56 89 4D FC 57 8B", 0x0);
//MAKE_SIGNATURE(CClientState_ProcessSetConVar, "engine.dll", "55 8B EC 83 EC 10 8B 45 08 53 8B D9 C7 45 ? ? ? ? ? 83 78 20 00 0F 8E ? ? ? ? 33 D2 56 89 55 F8 57", 0x0);

MAKE_HOOK(CClientState_ProcessSetConVar, S::CClientState_ProcessSetConVar(), bool, void* rcx, NET_SetConVar* msg)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CClientState_ProcessSetConVar[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, msg);
#endif

	return Vars::Misc::Game::RemoveForcedConVars.Value ? true : CALL_ORIGINAL(rcx, msg);
}