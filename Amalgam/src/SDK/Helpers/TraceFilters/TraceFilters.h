#pragma once

#include "../../Definitions/Interfaces/IEngineTrace.h"

<<<<<<< Updated upstream
enum
{
	SKIP_CHECK,
	FORCE_PASS,
	FORCE_HIT
};

enum
{
	WEAPON_INCLUDE,
	WEAPON_EXCLUDE
};
enum
{
	PLAYER_DEFAULT,
	PLAYER_NONE,
	PLAYER_ALL
};
enum
{
	OBJECT_DEFAULT,
	OBJECT_NONE,
	OBJECT_ALL
=======
class CTraceFilterEntitiesOnly : public ITraceFilter
{
public:
	bool ShouldHitEntity(IHandleEntity* pServerEntity, int contentsMask) override;
	TraceType_t	GetTraceType() const override;
	CBaseEntity* pSkip = nullptr;
>>>>>>> Stashed changes
};

class CTraceFilterHitscan : public ITraceFilter
{
public:
	bool ShouldHitEntity(IHandleEntity* pServerEntity, int nContentsMask) override;
	TraceType_t GetTraceType() const override;
	CBaseEntity* pSkip = nullptr;

	int iTeam = -1;
	std::vector<int> vWeapons = { TF_WEAPON_SNIPERRIFLE, TF_WEAPON_SNIPERRIFLE_CLASSIC, TF_WEAPON_SNIPERRIFLE_DECAP };
	int iType = FORCE_HIT;
	int iWeapon = WEAPON_EXCLUDE;
	bool bWeapon = false;
};

class CTraceFilterCollideable : public ITraceFilter
{
public:
	bool ShouldHitEntity(IHandleEntity* pServerEntity, int nContentsMask) override;
	TraceType_t GetTraceType() const override;
	CBaseEntity* pSkip = nullptr;

	int iTeam = -1;
	std::vector<int> vWeapons = { TF_WEAPON_CROSSBOW, TF_WEAPON_LUNCHBOX };
	int iType = FORCE_HIT;
	int iWeapon = WEAPON_INCLUDE;
	bool bWeapon = false;
	int iPlayer = PLAYER_DEFAULT;
	int iObject = OBJECT_ALL;
};

class CTraceFilterWorldAndPropsOnly : public ITraceFilter
{
public:
	bool ShouldHitEntity(IHandleEntity* pServerEntity, int nContentsMask) override;
	TraceType_t GetTraceType() const override;
	CBaseEntity* pSkip = nullptr;
<<<<<<< Updated upstream

	int iTeam = -1;
=======
};

class CTraceFilterNavigation : public ITraceFilter
{
public:
	bool ShouldHitEntity(IHandleEntity* pServerEntity, int nContentsMask) override;
	TraceType_t GetTraceType() const override;
};

class CTraceFilterWorldCustom : public ITraceFilter
{
public:
	bool ShouldHitEntity(IHandleEntity* pServerEntity, int contentsMask) override;
	TraceType_t GetTraceType() const override;
	CBaseEntity* pSkip = nullptr;
};

class CTraceFilterArc : public ITraceFilter
{
public:
	bool ShouldHitEntity(IHandleEntity* pServerEntity, int contentsMask) override;
	TraceType_t GetTraceType() const override;
	CBaseEntity* pSkip = nullptr;
>>>>>>> Stashed changes
};