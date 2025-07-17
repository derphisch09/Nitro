#include "../SDK/SDK.h"

MAKE_SIGNATURE(CTFPlayerInventory_VerifyChangedLoadoutsAreValid, "client.dll", "41 56 48 83 EC ? 48 8B 05 ? ? ? ? 48 8D 54 24", 0x0);

MAKE_HOOK(CTFPlayerInventory_VerifyChangedLoadoutsAreValid, S::CTFPlayerInventory_VerifyChangedLoadoutsAreValid(), void, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CTFPlayerInventory_VerifyChangedLoadoutsAreValid[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	if (!Vars::Misc::Exploits::EquipRegionUnlock.Value)
		CALL_ORIGINAL(rcx);
}