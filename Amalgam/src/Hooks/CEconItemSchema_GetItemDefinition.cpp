#include "../SDK/SDK.h"

//struct CEconItemDefinition_t
//{
//	byte pad0[524];
//	uint32 m_unEquipRegionMask;
//	uint32 m_unEquipRegionConflictMask;
//};

struct CEconItemDefinition_t
{
	DWORD dword0;
	KeyValues* m_pKVItem;
	WORD m_nDefIndex;
	DWORD dwordC;
	BYTE byte10;
	BYTE m_unMinItemLevel;
	BYTE m_unMaxItemLevel;
	BYTE gap13[3];
	WORD m_nDefaultDropQuantity;
	BYTE gap18[4];
	int int1C;
	DWORD dword20;
	BYTE gap24[4];
	DWORD dword28;
	DWORD dword2C;
	BYTE m_nPopularitySeed;
	const char* m_pszItemBaseName;
	bool m_bProperName;
	const char* m_pszItemTypeName;
	const char* m_pszItemDesc;
	DWORD m_rtExpiration;
	const char* m_pszInventoryModel;
	const char* m_pszInventoryImage;
	BYTE m_pszInventoryOverlayImages[20];
	int m_iInventoryImagePosition_0;
	int m_iInventoryImagePosition_1;
	int m_iInventoryImageSize_0;
	int m_iInventoryImageSize_1;
	int m_iInspectPanelDistance;
	const char* m_pszBaseDisplayModel;
	int m_iDefaultSkin;
	bool m_bLoadOnDemand;
	__declspec(align(2)) bool m_bHideBodyGroupsDeployedOnly;
	const char* m_pszWorldDisplayModel;
	const char* m_pszWorldExtraWearableModel;
	const char* m_pszWorldExtraWearableViewModel;
	const char* m_pszVisionFilteredDisplayModel;
	const char* m_pszCollectionReference;
	bool m_bAttachToHands;
	bool m_bAttachToHandsVMOnly;
	bool m_bFlipViewModel;
	bool m_bActAsWearable;
	bool m_bActAsWeapon;
	bool m_bIsTool;
	BYTE gap9E[30];
	const char* m_pszBrassModelOverride;
	void* m_pTool;
	DWORD dwordC4;
	int m_iCapabilities;
	BYTE gapCC[8];
	const char* m_pszItemClassname;
	const char* m_pszItemLogClassname;
	const char* m_pszItemIconClassname;
	const char* m_pszDefinitionName;
	const char* m_pszDatabaseAuditTable;
	bool m_bHidden;
	bool m_bShouldShowInArmory;
	bool m_bBaseItem;
	bool m_bImported;
	bool m_bIsPackBundle;
	BYTE gapED[11];
	const char* m_pszArmoryDesc;
	const char* m_pszXifierRemapClass;
	const char* m_pszBaseFunctionalItemName;
	const char* m_pszParticleSuffix;
	BYTE gap108[8];
	const char* m_pszArmoryRemap;
	const char* m_pszStoreRemap;
	const char* m_pszClassToken;
	const char* m_pszSlotToken;
	int m_iDropType;
	const char* m_pszHolidayRestriction;
	DWORD m_nVisionFilterFlags;
	DWORD m_iSubType;
	BYTE gap130[4];
	uint32 m_unEquipRegionMask;
	uint32 m_unEquipRegionConflictMask;
	WORD word13C;
	BYTE gap13E[22];
	bool m_bValidForShuffle;
	bool m_bValidForSelfMade;
	int int158;
	DWORD dword15C;
	BYTE gap160[4];
	char* pchar164;
	DWORD dword168;
};

MAKE_SIGNATURE(CEconItemSchema_GetItemDefinition, "client.dll", "89 54 24 ? 53 48 83 EC ? 48 8B D9 48 8D 54 24 ? 48 81 C1 ? ? ? ? E8 ? ? ? ? 85 C0", 0x0);

MAKE_HOOK(CEconItemSchema_GetItemDefinition, S::CEconItemSchema_GetItemDefinition(), CEconItemDefinition_t*, void* rcx, int iItemIndex)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CEconItemSchema_GetItemDefinition[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, iItemIndex);
#endif

	const auto pItemDefinition = CALL_ORIGINAL(rcx, iItemIndex);

	if (Vars::Misc::Exploits::EquipRegionUnlock.Value && pItemDefinition)
	{
		pItemDefinition->m_unEquipRegionMask = 0;
		pItemDefinition->m_unEquipRegionConflictMask = 0;
	}

	return pItemDefinition;
}