#pragma once

#include "IServerNetworkable.h"
#include "IServerUnknown.h"

#include "../Misc/String.h"
#include "../Interfaces.h"

class CMouthInfo;
struct SpatializationInfo_t;

class IServerEntity : public IServerUnknown
{
public:
	virtual ~IServerEntity() {}
	virtual int GetModelIndex(void) const = 0;
	virtual string_t GetModelName(void) const = 0;
	virtual void SetModelIndex(int index) = 0;

	inline ETFClassID GetClassID()
	{
		if (auto pNetworkable = GetNetworkable())
			return pNetworkable->GetClassID();

		return static_cast<ETFClassID>(0);
	}

	inline bool IsPlayer()
	{
		return GetClassID() == ETFClassID::CTFPlayer;
	}

	inline bool IsSentrygun()
	{
		return GetClassID() == ETFClassID::CObjectSentrygun;
	}

	inline bool IsDispenser()
	{
		return GetClassID() == ETFClassID::CObjectDispenser;
	}

	inline bool IsTeleporter()
	{
		return GetClassID() == ETFClassID::CObjectTeleporter;
	}

	inline bool IsBaseCombatWeapon()
	{
		return GetClassID() == ETFClassID::CBaseCombatWeapon;
	}

	inline bool IsWearable()
	{
		return GetClassID() == ETFClassID::CTFWearable;
	}

	inline bool IsBuilding()
	{
		switch (GetClassID())
		{
		case ETFClassID::CObjectDispenser:
		case ETFClassID::CObjectSentrygun:
		case ETFClassID::CObjectTeleporter: return true;
		default: return false;
		}
	}

	inline bool IsPickup()
	{
		switch (GetClassID())
		{
		case ETFClassID::CBaseAnimating: return GetModelName().ToCStr()[24] != 'h';
		case ETFClassID::CTFAmmoPack: return true;
		default: return false;
		}
	}

	inline bool IsNPC()
	{
		switch (GetClassID())
		{
		case ETFClassID::CHeadlessHatman:
		case ETFClassID::CTFTankBoss:
		case ETFClassID::CMerasmus:
		case ETFClassID::CZombie:
		case ETFClassID::CEyeballBoss:
			return true;
		default: return false;
		}
	}

	inline bool IsBomb()
	{
		switch (GetClassID())
		{
		case ETFClassID::CTFPumpkinBomb:
		case ETFClassID::CTFGenericBomb:
			return true;
		default: return false;
		}
	}

	template <typename T> inline T* As() { return reinterpret_cast<T*>(this); }
};