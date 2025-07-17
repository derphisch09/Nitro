#include "../SDK/SDK.h"

MAKE_SIGNATURE(CTFPlayer_ThirdPersonSwitch, "client.dll", "48 83 EC ? 48 8B 01 48 89 5C 24 ? 48 8B D9 48 89 7C 24", 0x0);

MAKE_HOOK(CTFPlayer_ThirdPersonSwitch, S::CTFPlayer_ThirdPersonSwitch(), void, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CTFPlayer_ThirdPersonSwitch[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	CALL_ORIGINAL(rcx);

	auto pLocal = H::Entities.GetLocal();

	if (!pLocal)
		return;

	const CBaseEntity* wep = pLocal->m_hActiveWeapon().Get();

	if (!wep || wep->As<CTFWeaponBase>()->GetWeaponID() != TF_WEAPON_MINIGUN)
		return;

	const CTFMinigun* minigun = wep->As<CTFMinigun>();

	if (!minigun || minigun->m_iState() != AC_STATE_FIRING)
		return;

	minigun->StartMuzzleEffect();
	minigun->StartBrassEffect();
}