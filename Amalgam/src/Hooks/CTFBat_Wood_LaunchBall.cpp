#include "../SDK/SDK.h"

MAKE_SIGNATURE(CTFBat_Wood_LaunchBall, "client.dll", "40 53 48 83 EC ? 48 8B D9 E8 ? ? ? ? 48 85 C0 74 ? 48 8B CB 48 83 C4 ? 5B E9 ? ? ? ? 48 83 C4 ? 5B C3 CC CC CC CC CC CC CC CC CC CC 48 89 5C 24", 0x0);

MAKE_HOOK(CTFBat_Wood_LaunchBall, S::CTFBat_Wood_LaunchBall(), void, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CTFBat_Wood_LaunchBall[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, pPlayer);
#endif
	auto pWeapon = reinterpret_cast<CTFWeaponBase*>(rcx);
	pWeapon->CalcIsAttackCritical();

	return CALL_ORIGINAL(rcx);
}