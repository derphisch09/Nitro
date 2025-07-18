#include "../SDK/SDK.h"

MAKE_SIGNATURE(CL_ProcessPacketEntities, "engine.dll", "48 89 7C 24 ? 4C 89 64 24 ? 55 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 4C 8B F9", 0x0);

class SVC_PacketEntities : public CNetMessage
{
	int	GetGroup() const 
	{ 
		return ENTITIES; 
	}

public:

	byte pad1[8];
	int m_nMaxEntries;
	int m_nUpdatedEntries;
	bool m_bIsDelta;
	bool m_bUpdateBaseline;
	int m_nBaseline;
	int m_nDeltaFrom;
	int m_nLength;
	bf_read m_DataIn;
	bf_write m_DataOut;
};

struct CriticalStorage_t
{
	float m_flCritTokenBucket;
	int m_nCritChecks;
	int m_nCritSeedRequests;
	int m_iLastCritCheckFrame;
	float m_flLastRapidFireCritCheckTime;
	float m_flCritTime;
};

MAKE_HOOK(CL_ProcessPacketEntities, S::CL_ProcessPacketEntities(), bool, SVC_PacketEntities* entmsg)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CL_ProcessPacketEntities[DEFAULT_BIND])
		return CALL_ORIGINAL(entmsg);
#endif

	if (entmsg->m_bIsDelta || G::Unload) // we won't need to restore
		return CALL_ORIGINAL(entmsg);

	CTFPlayer* pLocal = I::ClientEntityList->GetClientEntity(I::EngineClient->GetLocalPlayer())->As<CTFPlayer>();

	if (!pLocal)
	{
		SDK::Output("ProcessPacketEntities", "Failed to restore weapon crit data! (1)", { 255, 100, 100 });
		return CALL_ORIGINAL(entmsg);
	}

	if (!pLocal->m_hMyWeapons())
	{
		SDK::Output("ProcessPacketEntities", "Failed to restore weapon crit data! (2)", { 255, 100, 100 });
		return CALL_ORIGINAL(entmsg);
	}

	std::unordered_map<int, CriticalStorage_t> mCriticalStorage = {};

	for (int i = 0; i < MAX_WEAPONS; i++)
	{
		auto pWeapon = pLocal->GetWeaponFromSlot(i);

		if (!pWeapon)
			continue;

		mCriticalStorage[i].m_flCritTokenBucket = pWeapon->m_flCritTokenBucket();
		mCriticalStorage[i].m_nCritChecks = pWeapon->m_nCritChecks();
		mCriticalStorage[i].m_nCritSeedRequests = pWeapon->m_nCritSeedRequests();
		mCriticalStorage[i].m_iLastCritCheckFrame = pWeapon->m_iLastCritCheckFrame();
		mCriticalStorage[i].m_flLastRapidFireCritCheckTime = pWeapon->m_flLastRapidFireCritCheckTime();
		mCriticalStorage[i].m_flCritTime = pWeapon->m_flCritTime();

		if (Vars::Debug::Logging.Value) 
			I::CVar->ConsolePrintf("\n");

		SDK::Output("ProcessPacketEntities", std::format("{} ({:#x}): mCriticalStorage[i].m_flCritTokenBucket = {}", i, uintptr_t(pWeapon), pWeapon->m_flCritTokenBucket()).c_str(), { 100, 150, 255 }, Vars::Debug::Logging.Value);
		SDK::Output("ProcessPacketEntities", std::format("{} ({:#x}): mCriticalStorage[i].m_nCritChecks = {}", i, uintptr_t(pWeapon), pWeapon->m_nCritChecks()).c_str(), { 100, 150, 255 }, Vars::Debug::Logging.Value);
		SDK::Output("ProcessPacketEntities", std::format("{} ({:#x}): mCriticalStorage[i].m_nCritSeedRequests = {}", i, uintptr_t(pWeapon), pWeapon->m_nCritSeedRequests()).c_str(), { 100, 150, 255 }, Vars::Debug::Logging.Value);
		SDK::Output("ProcessPacketEntities", std::format("{} ({:#x}): mCriticalStorage[i].m_iLastCritCheckFrame = {}", i, uintptr_t(pWeapon), pWeapon->m_iLastCritCheckFrame()).c_str(), { 100, 150, 255 }, Vars::Debug::Logging.Value);
		SDK::Output("ProcessPacketEntities", std::format("{} ({:#x}): mCriticalStorage[i].m_flLastRapidFireCritCheckTime = {}", i, uintptr_t(pWeapon), pWeapon->m_flLastRapidFireCritCheckTime()).c_str(), { 100, 150, 255 }, Vars::Debug::Logging.Value);
		SDK::Output("ProcessPacketEntities", std::format("{} ({:#x}): mCriticalStorage[i].m_flCritTime = {}", i, uintptr_t(pWeapon), pWeapon->m_flCritTime()).c_str(), { 100, 150, 255 }, Vars::Debug::Logging.Value);
	}

	bool bReturn = CALL_ORIGINAL(entmsg);

	pLocal = I::ClientEntityList->GetClientEntity(I::EngineClient->GetLocalPlayer())->As<CTFPlayer>();

	if (!pLocal)
	{
		SDK::Output("ProcessPacketEntities", "Failed to restore weapon crit data! (3)", { 255, 100, 100 });
		return bReturn;
	}

	if (!pLocal->m_hMyWeapons())
	{
		SDK::Output("ProcessPacketEntities", "Failed to restore weapon crit data! (4)", { 255, 100, 100 });
		return bReturn;
	}

	for (auto& [iSlot, tStorage] : mCriticalStorage)
	{
		auto pWeapon = pLocal->GetWeaponFromSlot(iSlot);

		if (!pWeapon)
			break;

		pWeapon->m_flCritTokenBucket() = tStorage.m_flCritTokenBucket;
		pWeapon->m_nCritChecks() = tStorage.m_nCritChecks;
		pWeapon->m_nCritSeedRequests() = tStorage.m_nCritSeedRequests;
		pWeapon->m_iLastCritCheckFrame() = tStorage.m_iLastCritCheckFrame;
		pWeapon->m_flLastRapidFireCritCheckTime() = tStorage.m_flLastRapidFireCritCheckTime;
		pWeapon->m_flCritTime() = tStorage.m_flCritTime;

		if (Vars::Debug::Logging.Value)
			I::CVar->ConsolePrintf("\n");

		SDK::Output("ProcessPacketEntities", std::format("{} ({:#x}): pWeapon->m_flCritTokenBucket() = {}", iSlot, uintptr_t(pWeapon), pWeapon->m_flCritTokenBucket()).c_str(), { 100, 255, 150 }, Vars::Debug::Logging.Value);
		SDK::Output("ProcessPacketEntities", std::format("{} ({:#x}): pWeapon->m_nCritChecks() = {}", iSlot, uintptr_t(pWeapon), pWeapon->m_nCritChecks()).c_str(), { 100, 255, 150 }, Vars::Debug::Logging.Value);
		SDK::Output("ProcessPacketEntities", std::format("{} ({:#x}): pWeapon->m_nCritSeedRequests() = {}", iSlot, uintptr_t(pWeapon), pWeapon->m_nCritSeedRequests()).c_str(), { 100, 255, 150 }, Vars::Debug::Logging.Value);
		SDK::Output("ProcessPacketEntities", std::format("{} ({:#x}): pWeapon->m_iLastCritCheckFrame() = {}", iSlot, uintptr_t(pWeapon), pWeapon->m_iLastCritCheckFrame()).c_str(), { 100, 255, 150 }, Vars::Debug::Logging.Value);
		SDK::Output("ProcessPacketEntities", std::format("{} ({:#x}): pWeapon->m_flLastRapidFireCritCheckTime() = {}", iSlot, uintptr_t(pWeapon), pWeapon->m_flLastRapidFireCritCheckTime()).c_str(), { 100, 255, 150 }, Vars::Debug::Logging.Value);
		SDK::Output("ProcessPacketEntities", std::format("{} ({:#x}): pWeapon->m_flCritTime() = {}", iSlot, uintptr_t(pWeapon), pWeapon->m_flCritTime()).c_str(), { 100, 255, 150 }, Vars::Debug::Logging.Value);
	}

	return bReturn;
}