#include "../SDK/SDK.h"

MAKE_SIGNATURE(CTFRocketLauncher_FireProjectile, "client.dll", "48 89 74 24 ? 57 48 81 EC ? ? ? ? 48 8B FA 48 89 9C 24", 0x0);

MAKE_HOOK(CTFRocketLauncher_FireProjectile, S::CTFRocketLauncher_FireProjectile(), CBaseEntity*, void* rcx, CTFPlayer* pPlayer)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CTFRocketLauncher_FireProjectile[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, pPlayer);
#endif

	auto pWeapon = reinterpret_cast<CTFWeaponBase*>(rcx);
	pWeapon->m_bRemoveable() = false;
	return CALL_ORIGINAL(rcx, pPlayer);
}