#include "../SDK/SDK.h"

MAKE_SIGNATURE(CHudItemEffectMeterWeapon_CTFWeaponBase_IsEnabled, "client.dll", "48 83 EC ? E8 ? ? ? ? 48 85 C0 74 ? 45 33 C9 C6 44 24 ? ? 4C 8B C0 48 8D 15 ? ? ? ? 33 C9 E8 ? ? ? ? 85 C0 0F 95 C0 48 83 C4 ? C3 48 83 C4 ? C3 CC CC CC CC CC CC CC CC CC CC 8B 91", 0x0);

MAKE_HOOK(CHudItemEffectMeterWeapon_CTFWeaponBase_IsEnabled, S::CHudItemEffectMeterWeapon_CTFWeaponBase_IsEnabled(), bool)
{
	return Vars::Visuals::Other::KillstreakWeapons.Value ? true : CALL_ORIGINAL();
}