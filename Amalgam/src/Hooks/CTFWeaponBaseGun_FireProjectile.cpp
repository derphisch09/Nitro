#include "../SDK/SDK.h"

MAKE_SIGNATURE(CTFWeaponBaseGun_FireProjectile, "client.dll", "48 89 74 24 ? 57 48 81 EC ? ? ? ? 48 8B FA 48 89 9C 24", 0x0);

MAKE_HOOK(CTFWeaponBaseGun_FireProjectile, S::CTFWeaponBaseGun_FireProjectile(), CBaseEntity*, void* rcx, CTFPlayer* pPlayer)
{
	int iProjectile = 0;
	CALL_ATTRIB_HOOK_INT(iProjectile, override_projectile_type);

	if (iProjectile == 0)
		iProjectile = GetWeaponProjectileType();

	CBaseEntity* pProjectile = NULL;

	switch (iProjectile)
	{
	case TF_PROJECTILE_BULLET:
		FireBullet(pPlayer);
		break;
	case TF_PROJECTILE_ROCKET:
		pProjectile = FireRocket(pPlayer, iProjectile);
		pPlayer->DoAnimationEvent(PLAYERANIMEVENT_ATTACK_PRIMARY);
		break;
	}

	//reinterpret_cast<CBaseEntity*>(rcx)->m_vecOrigin();

	//float flTime = I::GlobalVars->curtime;
	//float flAttack = pPlayer->m_flNextAttack();

	//SDK::Output("FireProjectile", std::format("{}, {}, {}", flTime - flAttack, TIME_TO_TICKS(flAttack - flTime), flTime < flAttack).c_str());

	return CALL_ORIGINAL(rcx, pPlayer);
}