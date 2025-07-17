#include "../SDK/SDK.h"

MAKE_SIGNATURE(GenerateEquipRegionConflictMask, "client.dll", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 33 FF 41 8B E8", 0x0);

MAKE_HOOK(GenerateEquipRegionConflictMask, S::GenerateEquipRegionConflictMask(), uint32_t, int iClass, int iUpToSlot, int iIgnoreSlot)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::GenerateEquipRegionConflictMask[DEFAULT_BIND])
		return CALL_ORIGINAL(iClass, iUpToSlot, iIgnoreSlot);
#endif

	return Vars::Misc::Exploits::EquipRegionUnlock.Value ? 0 : CALL_ORIGINAL(iClass, iUpToSlot, iIgnoreSlot);
}