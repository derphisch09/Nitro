#include "../SDK/SDK.h"

MAKE_SIGNATURE(CWeaponMedigun_WeaponIdle, "client.dll", "40 53 48 83 EC 20 48 8B 01 48 8B D9 FF 90 ? ? ? ? 84 C0 74 2A", 0x0);

MAKE_HOOK(CWeaponMedigun_WeaponIdle, S::CWeaponMedigun_WeaponIdle(), void, CWeaponMedigun* const rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CWeaponMedigun_WeaponIdle[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	if (!rcx)
	{
		CALL_ORIGINAL(rcx);
		return;
	}

	auto pLocal = H::Entities.GetLocal();

	if (!pLocal)
	{
		CALL_ORIGINAL(rcx);
		return;
	}

	if ((pLocal->m_afButtonPressed() & IN_RELOAD) && rcx->GetMedigunType() == MEDIGUN_RESIST && !rcx->IsReleasingCharge())
	{
		rcx->m_nChargeResistType() += 1;
		rcx->m_nChargeResistType() = rcx->m_nChargeResistType() % MEDIGUN_NUM_RESISTS;
	}

	CALL_ORIGINAL(rcx);
}