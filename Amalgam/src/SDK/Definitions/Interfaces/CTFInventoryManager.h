#pragma once

#include "Interface.h"

MAKE_SIGNATURE(CTFPlayerInventory_GetFirstItemOfItemDef, "client.dll", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B FA 0F B7 E9", 0x0)
//MAKE_SIGNATURE(CTFInventoryManager_GetItemByBackpackPosition, "client.dll", "55 8B EC 83 EC 08 8B 01", 0x0);

class CEconItemView
{
public:
	VIRTUAL(GetDefinitionIndex, uint32_t, 48, this);

	inline uint64_t UUID()
	{
		uint64_t value = *reinterpret_cast<uint64_t*>(this + 96);
		auto a = value >> 32;
		auto b = value << 32;
		return b | a;
	}
};

#define SIZE_OF_ITEMVIEW 344

class CTFPlayerInventory
{
public:
	SIGNATURE_ARGS(GetFirstItemOfItemDef, CEconItemView*, CTFPlayerInventory, (uint32_t iItemDef), iItemDef, this);

	VIRTUAL(GetItemCount, int, 112, this);

	inline CEconItemView* GetItem(int idx)
	{
		uintptr_t uStart = *(uintptr_t*)(this + 96);
		uintptr_t nOffset = idx * SIZE_OF_ITEMVIEW;
		return reinterpret_cast<CEconItemView*>(uStart + nOffset);
	}

	inline std::vector<uint64_t> GetItemsOfItemDef(uint32_t iItemDef)
	{
		std::vector<uint64_t> vUUIDs;

		for (int i = 0; i < GetItemCount(); i++)
		{
			auto pItem = GetItem(i);

			if (pItem->GetDefinitionIndex() == iItemDef)
				vUUIDs.push_back(pItem->UUID());
		}

		return vUUIDs;
	}
};

class CTFInventoryManager
{
public:
	//SIGNATURE_ARGS(GetItemByBackpackPosition, void*, CTFInventoryManager, (int iBackpackPosition), this, iBackpackPosition);

	VIRTUAL_ARGS(EquipItemInLoadout, bool, 19, (int iClass, int iSlot, uint64_t uniqueid), this, iClass, iSlot, uniqueid);
	VIRTUAL(GetLocalInventory, CTFPlayerInventory*, 23, this);
};

MAKE_INTERFACE_SIGNATURE(CTFInventoryManager, TFInventoryManager, "client.dll", "48 8D 05 ? ? ? ? C3 CC CC CC CC CC CC CC CC 48 83 EC ? 4C 8D 0D", 0x0, 0);