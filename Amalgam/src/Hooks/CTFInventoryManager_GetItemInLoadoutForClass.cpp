#include "../SDK/SDK.h"

MAKE_SIGNATURE(CTFInventoryManager_GetItemInLoadoutForClass, "client.dll", "48 8B C4 48 89 58 ? 48 89 68 ? 48 89 70 ? 57 48 83 EC ? 81 60", 0x0);
MAKE_SIGNATURE(CEquipSlotItemSelectionPanel_UpdateModelPanelsForSelection_GetItemInLoadoutForClass_Call, "client.dll", "48 85 C0 74 ? 48 8D 48 ? 48 8B 40 ? FF 50 ? 44 0B A0", 0x0);

MAKE_HOOK(CTFInventoryManager_GetItemInLoadoutForClass, S::CTFInventoryManager_GetItemInLoadoutForClass(), void*, void* rcx, int iClass, int iSlot, CSteamID* pID)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CTFInventoryManager_GetItemInLoadoutForClass[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, iClass, iSlot, pID);
#endif

	static const auto dwDesired = S::CEquipSlotItemSelectionPanel_UpdateModelPanelsForSelection_GetItemInLoadoutForClass_Call();
	const auto dwRetAddr = uintptr_t(_ReturnAddress());

	return dwRetAddr == dwDesired && Vars::Misc::Exploits::EquipRegionUnlock.Value ? nullptr : CALL_ORIGINAL(rcx, iClass, iSlot, pID);
}