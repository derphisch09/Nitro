#include "../SDK/SDK.h"

MAKE_SIGNATURE(CClientPrecipitation_Simulate, "client.dll", "55 8B EC 83 EC 10 53 8B D9 8B 03 FF 50 7C E8 ? ? ? ? F3 0F 2A C0 F3 0F 59 05 ? ? ? ? F3 0F 11 83 ? ? ? ? F3 0F 10 45 ? 0F 2E 05 ? ? ? ? 9F F6 C4 44 7B 05 E8 ? ? ? ? 8B 83 ? ? ? ? 83 F8 02 75 0E 8B CB E8", 0x0);

MAKE_HOOK(CClientPrecipitation_Simulate, S::CClientPrecipitation_Simulate(), void, void* rcx, float dt)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CClientPrecipitation_Simulate[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, dt);
#endif

	return CALL_ORIGINAL(rcx, dt);
}