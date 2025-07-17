#include "../SDK/SDK.h"
#include "../Features/Ticks/Ticks.h"

MAKE_SIGNATURE(CBaseEntity_InterpolateServerEntities, "client.dll", "4C 8B DC 41 54 41 55 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 45 33 ED 49 89 5B ? 48 8D 1D", 0x0);

MAKE_HOOK(CBaseEntity_InterpolateServerEntities, S::CBaseEntity_InterpolateServerEntities(), void, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CBaseEntity_InterpolateServerEntities[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	if (auto pLocal = H::Entities.GetLocal())
	{
		if (F::Ticks->m_bRecharge && !I::Input->CAM_IsThirdPerson() && pLocal->IsAlive())
			return;
	}

	CALL_ORIGINAL(rcx);
}