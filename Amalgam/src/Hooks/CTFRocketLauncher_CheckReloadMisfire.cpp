#include "../SDK/SDK.h"

MAKE_SIGNATURE(CTFRocketLauncher_CheckReloadMisfire, "client.dll", "48 83 EC ? E8 ? ? ? ? 32 C0", 0x0);

MAKE_HOOK(CTFRocketLauncher_CheckReloadMisfire, S::CTFRocketLauncher_CheckReloadMisfire(), bool, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CTFRocketLauncher_CheckReloadMisfire[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	auto pWeapon = reinterpret_cast<CTFWeaponBase*>(rcx);

	if (!SDK::AttribHookValue(0, "can_overload", pWeapon))
		return false;

	auto pPlayer = pWeapon->m_hOwner()->As<CTFPlayer>();
	int iClip1 = pWeapon->m_iClip1();

	if (pWeapon->m_bRemoveable())
	{
		if (iClip1 > 0)
		{
			pWeapon->CalcIsAttackCritical();
			return true;
		}
		else
			pWeapon->m_bRemoveable() = false;
	}
	else if (iClip1 >= pWeapon->GetMaxClip1() || iClip1 > 0 && pPlayer && pPlayer->GetAmmoCount(pWeapon->m_iPrimaryAmmoType()) == 0)
	{
		pWeapon->CalcIsAttackCritical();
		pWeapon->m_bRemoveable() = true;
		return true;
	}

	return false;
}