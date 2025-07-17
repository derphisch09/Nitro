#include "CBaseCombatCharacter.h"

#include "../../SDK.h"

CHandle<CTFWeaponBase>(&CBaseCombatCharacter::m_hMyWeapons())[MAX_WEAPONS]
{
	static int nOffset = U::NetVars.GetNetVar("CBaseCombatCharacter", "m_hMyWeapons");
	return *reinterpret_cast<CHandle<CTFWeaponBase>(*)[MAX_WEAPONS]>(uintptr_t(this) + nOffset);
}

CTFWeaponBase* CBaseCombatCharacter::GetWeaponFromSlot(int nSlot)
{
	if (nSlot < 0 || nSlot >= MAX_WEAPONS)
		return nullptr;

	return m_hMyWeapons()[nSlot].Get();
}

CTFWeaponBase* CBaseCombatCharacter::FindWeaponByItemDefinitionIndex(int definition_index)
{
	for (int n; n < MAX_WEAPONS; n++)
	{
		CTFWeaponBase* weapon = GetWeaponFromSlot(n);

		if (!weapon)
			continue;

		if (weapon->m_iItemDefinitionIndex() == definition_index)
			return weapon;
	}

	return nullptr;
}