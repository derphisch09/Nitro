#pragma once
#include "CBaseHandle.h"
#include "IClientEntity.h"
#include "CCollisionProperty.h"
#include "CParticleProperty.h"
#include "../Main/UtlVector.h"
#include "../Definitions.h"
#include "../../../Utils/Memory/Memory.h"
#include "../../../Utils/Signatures/Signatures.h"
#include "../../../Utils/NetVars/NetVars.h"

MAKE_SIGNATURE(CBaseEntity_SetAbsOrigin, "client.dll", "48 89 5C 24 ? 57 48 83 EC ? 48 8B FA 48 8B D9 E8 ? ? ? ? F3 0F 10 83", 0x0);
MAKE_SIGNATURE(CBaseEntity_SetAbsAngles, "client.dll", "48 89 5C 24 ? 57 48 81 EC ? ? ? ? 48 8B FA 48 8B D9 E8 ? ? ? ? F3 0F 10 83", 0x0);
MAKE_SIGNATURE(CBaseEntity_SetAbsVelocity, "client.dll", "48 89 5C 24 ? 57 48 83 EC ? F3 0F 10 81 ? ? ? ? 48 8B DA 0F 2E 02", 0x0);
MAKE_SIGNATURE(CBaseEntity_EstimateAbsVelocity, "client.dll", "48 89 5C 24 ? 57 48 83 EC ? 48 8B FA 48 8B D9 E8 ? ? ? ? 48 3B D8", 0x0);
MAKE_SIGNATURE(CBaseEntity_CreateShadow, "client.dll", "48 89 5C 24 ? 57 48 83 EC ? 48 8B 41 ? 48 8B F9 48 83 C1 ? FF 90", 0x0);
MAKE_SIGNATURE(CBaseEntity_InvalidateBoneCache, "client.dll", "8B 05 ? ? ? ? FF C8 C7 81", 0x0);
MAKE_SIGNATURE(CBaseEntity_ShouldCollide, "client.dll", "83 B9 ? ? ? ? ? 75 ? 41 C1 E8", 0x0);
MAKE_SIGNATURE(CBaseEntity_RestoreData, "client.dll", "E8 ? ? ? ? 48 8B CF 8B D8 E8 ? ? ? ? 48 85 C0", 0x0);
MAKE_SIGNATURE(CBaseEntity_CalcAbsoluteVelocity, "client.dll", "40 57 48 81 EC 90 00 00 00 F7", 0x0);
MAKE_SIGNATURE(CBaseEntity_BlocksLOS, "client.dll", "E8 ? ? ? ? 84 C0 74 ? B0 ? 48 83 C4 ? 5B C3 32 C0 48 83 C4 ? 5B C3 CC CC CC CC CC CC CC CC CC CC CC CC CC CC CC", 0x0);
//MAKE_SIGNATURE(CBaseEntity_GetPredictionRandomSeed, "client.dll", "0F B6 1D ? ? ? ? 89 9D", 0x3);
MAKE_SIGNATURE(CBaseEntity_SetPredictionRandomSeed, "client.dll", "48 85 C9 75 ? C7 05 ? ? ? ? ? ? ? ? C3", 0x0);
MAKE_SIGNATURE(CBaseEntity_SetPredictionPlayer, "client.dll", "48 89 3D ? ? ? ? 66 0F 6E 87", 0x0);
MAKE_SIGNATURE(CBaseEntity_PhysicsRunThink, "client.dll", "4C 8B DC 49 89 73 ? 57 48 81 EC ? ? ? ? 8B 81", 0x0);
MAKE_SIGNATURE(CBaseEntity_GetNextThinkTick, "client.dll", "E8 ? ? ? ? 85 C0 7E ? 3B 87", 0x0);
MAKE_SIGNATURE(CBaseEntity_SaveData, "client.dll", "E8 ? ? ? ? FF C7 83 FF 5A", 0x0);
MAKE_SIGNATURE(CBaseEntity_GetPredictedFrame, "client.dll", "48 83 B9 48 07 00 00 00 44", 0x0);
MAKE_SIGNATURE(CBaseEntity_SetLocalAngles, "client.dll", "48 89 5C 24 08 57 48 83 EC 20 F3 0F 10 81 C8", 0x0);
MAKE_SIGNATURE(CBaseEntity_SetNextThink, "client.dll", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 0F 2E 0D", 0x0);

enum CollideType_t
{
	ENTITY_SHOULD_NOT_COLLIDE = 0,
	ENTITY_SHOULD_COLLIDE,
	ENTITY_SHOULD_RESPOND
};

typedef CHandle<CBaseEntity> EHANDLE;

#define MULTIPLAYER_BACKUP 90

class IInterpolatedVar;

class VarMapEntry_t
{
public:
	unsigned short type;
	unsigned short m_bNeedsToInterpolate;
	void* data;
	IInterpolatedVar* watcher;
};

struct VarMapping_t
{
	CUtlVector<VarMapEntry_t> m_Entries;
	int m_nInterpolatedEntries;
	float m_lastInterpolationTime;
};

enum ThinkMethods_t
{
	THINK_FIRE_ALL_FUNCTIONS,
	THINK_FIRE_BASE_ONLY,
	THINK_FIRE_ALL_BUT_BASE,
};

class CBaseEntity : public IClientEntity
{
public:
	NETVAR(m_flAnimTime, float, "CBaseEntity", "m_flAnimTime");
	NETVAR(m_flSimulationTime, float, "CBaseEntity", "m_flSimulationTime");
	NETVAR(m_ubInterpolationFrame, int, "CBaseEntity", "m_ubInterpolationFrame");
	NETVAR(m_vecOrigin, Vec3, "CBaseEntity", "m_vecOrigin");
	NETVAR(m_angRotation, Vec3, "CBaseEntity", "m_angRotation");
	NETVAR(m_nModelIndex, int, "CBaseEntity", "m_nModelIndex");
	NETVAR(m_fEffects, int, "CBaseEntity", "m_fEffects");
	NETVAR(m_nRenderMode, int, "CBaseEntity", "m_nRenderMode");
	NETVAR(m_nRenderFX, int, "CBaseEntity", "m_nRenderFX");
	NETVAR(m_clrRender, Color_t, "CBaseEntity", "m_clrRender");
	NETVAR(m_iTeamNum, int, "CBaseEntity", "m_iTeamNum");
	NETVAR(m_CollisionGroup, int, "CBaseEntity", "m_CollisionGroup");
	NETVAR(m_flElasticity, float, "CBaseEntity", "m_flElasticity");
	NETVAR(m_flShadowCastDistance, float, "CBaseEntity", "m_flShadowCastDistance");
	NETVAR(m_hOwnerEntity, EHANDLE, "CBaseEntity", "m_hOwnerEntity");
	NETVAR(m_hEffectEntity, EHANDLE, "CBaseEntity", "m_hEffectEntity");
	NETVAR(moveparent, int, "CBaseEntity", "moveparent");
	NETVAR(m_iParentAttachment, int, "CBaseEntity", "m_iParentAttachment");
	NETVAR(m_Collision, CCollisionProperty*, "CBaseEntity", "m_Collision");
	NETVAR(m_vecMinsPreScaled, Vec3, "CBaseEntity", "m_vecMinsPreScaled");
	NETVAR(m_vecMaxsPreScaled, Vec3, "CBaseEntity", "m_vecMaxsPreScaled");
	NETVAR(m_vecMins, Vec3, "CBaseEntity", "m_vecMins");
	NETVAR(m_vecMaxs, Vec3, "CBaseEntity", "m_vecMaxs");
	NETVAR(m_nSolidType, int, "CBaseEntity", "m_nSolidType");
	NETVAR(m_usSolidFlags, int, "CBaseEntity", "m_usSolidFlags");
	NETVAR(m_nSurroundType, int, "CBaseEntity", "m_nSurroundType");
	NETVAR(m_triggerBloat, int, "CBaseEntity", "m_triggerBloat");
	NETVAR(m_bUniformTriggerBloat, bool, "CBaseEntity", "m_bUniformTriggerBloat");
	NETVAR(m_vecSpecifiedSurroundingMinsPreScaled, Vec3, "CBaseEntity", "m_vecSpecifiedSurroundingMinsPreScaled");
	NETVAR(m_vecSpecifiedSurroundingMaxsPreScaled, Vec3, "CBaseEntity", "m_vecSpecifiedSurroundingMaxsPreScaled");
	NETVAR(m_vecSpecifiedSurroundingMins, Vec3, "CBaseEntity", "m_vecSpecifiedSurroundingMins");
	NETVAR(m_vecSpecifiedSurroundingMaxs, Vec3, "CBaseEntity", "m_vecSpecifiedSurroundingMaxs");
	NETVAR(m_iTextureFrameIndex, int, "CBaseEntity", "m_iTextureFrameIndex");
	NETVAR(m_PredictableID, int, "CBaseEntity", "m_PredictableID");
	NETVAR(m_bIsPlayerSimulated, bool, "CBaseEntity", "m_bIsPlayerSimulated");
	NETVAR(m_bSimulatedEveryTick, bool, "CBaseEntity", "m_bSimulatedEveryTick");
	NETVAR(m_bAnimatedEveryTick, bool, "CBaseEntity", "m_bAnimatedEveryTick");
	NETVAR(m_bAlternateSorting, bool, "CBaseEntity", "m_bAlternateSorting");
	NETVAR(m_nModelIndexOverrides, void*, "CBaseEntity", "m_nModelIndexOverrides");
	NETVAR(movetype, int, "CBaseEntity", "movetype");

	//NETVAR_OFF(EHANDLE, GetMoveParent, "CBaseEntity", "moveparent", -16);
	//NETVAR_OFF(EHANDLE, FirstMoveChild, "CBaseEntity", "moveparent", -12);
	//NETVAR_OFF(EHANDLE, NextMovePeer, "CBaseEntity", "moveparent", -8);
	NETVAR_OFF(m_flOldSimulationTime, float, "CBaseEntity", "m_flSimulationTime", 4);
	NETVAR_OFF(m_flGravity, float, "CTFPlayer", "m_nWaterLevel", -24);
	NETVAR_OFF(m_MoveType, byte, "CTFPlayer", "m_nWaterLevel", -4);
	NETVAR_OFF(m_MoveCollide, byte, "CTFPlayer", "m_nWaterLevel", -3);
	NETVAR_OFF(m_nWaterType, byte, "CTFPlayer", "m_nWaterLevel", 1);
	NETVAR_OFF(m_Particles, CParticleProperty*, "CBaseEntity", "m_flElasticity", -56);
	NETVAR_OFF(m_bPredictable, bool, "CBaseEntity", "m_iParentAttachment", 5);
	NETVAR_OFF(m_pOriginalData, uint8_t*, "CBaseEntity", "m_bIsPlayerSimulated", -12);
	NETVAR_OFF(m_pIntermediateData, uint8_t**, "CBaseEntity", "m_vecOrigin", 32);
	NETVAR_OFF(m_MoveType, unsigned char, "CTFPlayer", "m_nWaterLevel", -4);
	NETVAR_OFF(m_MoveCollide, unsigned char, "CTFPlayer", "m_nWaterLevel", -3);

	inline CBaseEntity* GetMoveParent()
	{
		static int nOffset = U::NetVars.GetNetVar("CBaseEntity", "moveparent") - 8;
		auto m_pMoveParent = reinterpret_cast<EHANDLE*>(uintptr_t(this) + nOffset);

		return m_pMoveParent ? m_pMoveParent->Get() : nullptr;
	}

	inline CBaseEntity* NextMovePeer()
	{
		static int nOffset = U::NetVars.GetNetVar("CBaseEntity", "moveparent") - 16;
		auto m_pMovePeer = reinterpret_cast<EHANDLE*>(uintptr_t(this) + nOffset);

		return m_pMovePeer ? m_pMovePeer->Get() : nullptr;
	}

	inline CBaseEntity* FirstMoveChild()
	{
		static int nOffset = U::NetVars.GetNetVar("CBaseEntity", "moveparent") - 24;
		auto m_pMoveChild = reinterpret_cast<EHANDLE*>(uintptr_t(this) + nOffset);

		return m_pMoveChild ? m_pMoveChild->Get() : nullptr;
	}

<<<<<<< Updated upstream
	VIRTUAL(EyePosition, Vec3, 142, this);
	VIRTUAL(EyeAngles, Vec3&, 143, this);
=======
	OFFSET(m_vecAbsVelocity, Vec3, 472);
	OFFSET(m_vecOldOrigin, Vec3, 824);
	OFFSET(m_vecNetworkOrigin, Vec3, 1096);

>>>>>>> Stashed changes
	VIRTUAL(UpdateVisibility, void, 91, this);
	VIRTUAL(Think, void, 122, this);
	VIRTUAL(PreThink, void, 262, this);
	VIRTUAL(PostThink, void, 263, this);
	VIRTUAL(GetPredDescMap, datamap_t*, 15, this);

	VIRTUAL_ARGS(ShouldCollide, bool, 146, (int collisionGroup, int contentsMask), this, collisionGroup, contentsMask);

	SIGNATURE_ARGS(SetAbsOrigin, void, CBaseEntity, (const Vec3& vOrigin), this, std::ref(vOrigin));
	SIGNATURE_ARGS(SetAbsAngles, void, CBaseEntity, (const Vec3& vAngles), this, std::ref(vAngles));
	SIGNATURE_ARGS(SetAbsVelocity, void, CBaseEntity, (const Vec3& vVelocity), this, std::ref(vVelocity));
	SIGNATURE_ARGS(EstimateAbsVelocity, void, CBaseEntity, (Vec3& vVelocity), this, std::ref(vVelocity));

	SIGNATURE(InvalidateBoneCache, void, CBaseEntity, this);
	SIGNATURE(CreateShadow, void, CBaseEntity, this);
	SIGNATURE(CalcAbsoluteVelocity, void, CBaseEntity, this);
	SIGNATURE(BlocksLOS, bool, CBaseEntity, this);
	//SIGNATURE(GetPredictionRandomSeed, int, CBaseEntity, this);

	SIGNATURE_ARGS(SetPredictionRandomSeed, void, CBaseEntity, (const CUserCmd* cmd), this, cmd);
	SIGNATURE_ARGS(SetPredictionPlayer, void, CBaseEntity, (CBasePlayer* player), this, player);
	SIGNATURE_ARGS(PhysicsRunThink, void, CBaseEntity, (ThinkMethods_t thinkMethod = THINK_FIRE_ALL_FUNCTIONS), this, thinkMethod);
	SIGNATURE_ARGS(GetNextThinkTick, int, CBaseEntity, (const char* szContext = nullptr), this, szContext);
	SIGNATURE_ARGS(SaveData, int, CBaseEntity, (const char* context, int slot, int type), this, context, slot, type);
	SIGNATURE_ARGS(RestoreData, int, CBaseEntity, (const char* context, int slot, int type), this, context, slot, type);
	SIGNATURE_ARGS(GetPredictedFrame, void*, CBaseEntity, (int framenumber), this, framenumber);
	SIGNATURE_ARGS(SetLocalAngles, void*, CBaseEntity, (Vec3& ang), this, ang);

	inline const Vec3& GetAbsoluteVelocity()
	{
		const_cast<CBaseEntity*>(this)->CalcAbsoluteVelocity();
		return m_vecAbsVelocity();
	}

	inline Vec3 GetAbsVelocity()
	{
		Vec3 vOut;
		EstimateAbsVelocity(vOut);
		return vOut;
	}

	inline void SetPredictionBasePlayer(CBasePlayer* player)
	{
		*reinterpret_cast<CBasePlayer**>(*reinterpret_cast<DWORD*>(S::CBaseEntity_SetPredictionPlayer() + 0x03) + S::CBaseEntity_SetPredictionPlayer() + 0x07) = player;
	}

	inline bool SetPhysicsRunThink(ThinkMethods_t thinkMethod = THINK_FIRE_ALL_FUNCTIONS)
	{
		//return S::CBaseEntity_PhysicsRunThink.As<bool(__thiscall*)(void*, ThinkMethods_t)>()(this, thinkMethod);

		static auto fnPhysicsRunThink = S::CBaseEntity_PhysicsRunThink.As<bool(__thiscall*)(void*, ThinkMethods_t)>();
		return fnPhysicsRunThink(this, thinkMethod);
	}

	//inline bool SetPhysicsRunThink(int thinkMethod = 0)
	//{
	//	static auto fnPhysicsRunThink = S::CBaseEntity_PhysicsRunThink.As<bool(__thiscall*)(void*, int)>();
	//	return fnPhysicsRunThink(this, thinkMethod);
	//}

	inline void SetNextThink(float thinkTime, const char* szContext)
	{
		static auto fnSetNextThink = S::CBaseEntity_SetNextThink.As<void(__thiscall*)(void*, float, const char*)>();
		fnSetNextThink(this, thinkTime, szContext);
	}

	Vec3 GetSize();
	Vec3 GetOffset();
	Vec3 GetCenter();
	Vec3 GetRenderCenter();
	Vec3 GetOBBSize();
	int IsInValidTeam();
	int SolidMask();
	void* GetOriginalNetworkDataObject();
	size_t GetIntermediateDataSize();
};