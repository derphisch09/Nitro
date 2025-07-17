#include "../SDK/SDK.h"

MAKE_SIGNATURE(CClientPrecipitation_SimulateRain, "client.dll", "55 8B EC A1 ? ? ? ? 83 EC 60 F3 0F 10 40 ? 53 57 8B 7D 08 8B D9 F3 0F 5C 47 ? F3 0F 10 8B ? ? ? ? F3 0F 5C C8 0F 57 C0 0F 2F C1 0F 87 ? ? ? ? 8B 07 B9 ? ? ? ? F3 0F 10 4D ? 89 45 F4 0F 28 C1 8B 47 04 F3 0F 59 47", 0x0);

MAKE_HOOK(CClientPrecipitation_SimulateRain, S::CClientPrecipitation_SimulateRain(), bool, void* rcx, void* pParticle, float dt)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CClientPrecipitation_SimulateRain[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, pParticle, dt);
#endif

	return CALL_ORIGINAL(rcx, pParticle, dt);
}