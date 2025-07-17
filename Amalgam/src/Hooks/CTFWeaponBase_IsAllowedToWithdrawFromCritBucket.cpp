#include "../SDK/SDK.h"
#include "../Features/CritHack/CritHack.h"

MAKE_SIGNATURE(CTFWeaponBase_IsAllowedToWithdrawFromCritBucket, "client.dll", "E8 ? ? ? ? 0F B6 D8 84 C0 74 ? 40 84 ED", 0x0);

MAKE_HOOK(CTFWeaponBase_IsAllowedToWithdrawFromCritBucket, S::CTFWeaponBase_IsAllowedToWithdrawFromCritBucket(), void, void* rcx, float flDamage)
{
		F::CritHack.IsAllowedToWithdrawFromCritBucketHandler(flDamage);
		return CALL_ORIGINAL(rcx, flDamage);

}