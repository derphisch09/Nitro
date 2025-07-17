#pragma once
#include "Interface.h"
#include "../Steam/SteamClientPublic.h"

MAKE_SIGNATURE(CGCClientSharedObjectCache_FindTypeCache, "client.dll", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 0F B7 59 ? BE", 0x0);

//MAKE_SIGNATURE(CTFGCClientSystem_Init, "client.dll", "56 57 8B F9 8D B7 ? ? ? ? C6 46", 0x0);
//MAKE_SIGNATURE(CTFGCClientSystem_PreInitGC, "client.dll", "56 8B F1 80 BE ? ? ? ? ? 0F 85 ? ? ? ? 68", 0x0);
//MAKE_SIGNATURE(CTFGCClientSystem_PostInit, "client.dll", "E9 ? ? ? ? CC CC CC CC CC CC CC CC CC CC CC 55 8B EC 83 EC ? 56 68", 0x0);
//MAKE_SIGNATURE(CTFGCClientSystem_PostInitGC, "client.dll", "55 8B EC 83 EC ? 56 68 ? ? ? ? 8B F1 FF 15 ? ? ? ? A1 ? ? ? ? 83 C4 ? 85 C0 74 ? 83 78 ? ? 74 ? 68 ? ? ? ? FF 15 ? ? ? ? A1 ? ? ? ? 8D 55 ? 83 C4 ? 8B 48 ? 52 8B 01 FF 50 ? 8D 86", 0x0);
//MAKE_SIGNATURE(CTFGCClientSystem_ReceivedClientWelcome, "client.dll", "55 8B EC 81 EC ? ? ? ? 56 57 FF 75 ? 8B F9 E8 ? ? ? ? 68", 0x0);

//MAKE_SIGNATURE(CTFGCClientSystem_Shutdown, "client.dll", "55 8B EC 83 EC ? 56 68 ? ? ? ? 8B F1 FF 15 ? ? ? ? A1 ? ? ? ? 83 C4 ? 85 C0 74 ? 83 78 ? ? 74 ? 68 ? ? ? ? FF 15 ? ? ? ? A1 ? ? ? ? 8D 55 ? 83 C4 ? 8B 48 ? 52 8B 01 FF 50 ? 8D 45", 0x0);
//MAKE_SIGNATURE(CTFGCClientSystem_Update, "client.dll", "55 8B EC D9 45 ? 83 EC ? 53 56", 0x0);
//MAKE_SIGNATURE(CTFGCClientSystem_BHaveLiveMatch, "client.dll", "56 8B F1 8D 8E ? ? ? ? E8 ? ? ? ? 84 C0 74", 0x0);
//MAKE_SIGNATURE(CTFGCClientSystem_GetNumMatchInvites, "client.dll", "8B 89 ? ? ? ? 85 C9 74 ? 68 ? ? ? ? E8 ? ? ? ? 85 C0 74 ? 8B 40", 0x0);

//MAKE_SIGNATURE(CTFGCClientSystem_BConnectedToMatchServer, "client.dll", "55 8B EC 53 8A 5D ? 56 8B F1 84 DB 74 ? 8D 8E", 0x0);
//MAKE_SIGNATURE(CTFGCClientSystem_BGetLocalPlayerBadgeInfoForTour, "client.dll", "55 8B EC 83 EC ? 8B 45 ? 56 C7 00", 0x0);
//MAKE_SIGNATURE(CTFGCClientSystem_BIsMatchGroupDisabled, "client.dll", "55 8B EC 51 56 8B B1 ? ? ? ? 33 D2 C7 45", 0x0);

//MAKE_SIGNATURE(CTFGCClientSystem_ConnectToServer, "client.dll", "55 8B EC 51 57 FF 75 ? 8B F9 68", 0x0);
//MAKE_SIGNATURE(CTFGCClientSystem_DumpPing, "client.dll", "55 8B EC 83 EC ? 57 8B F9 C7 45 ? ? ? ? ? 8B 87", 0x0);
//MAKE_SIGNATURE(CTFGCClientSystem_FireGameEvent, "client.dll", "55 8B EC 53 8B 5D ? 56 8B F1 8B CB 57 8B 03 FF 50 ? 8B F8 68", 0x0);
//MAKE_SIGNATURE(CTFGCClientSystem_GetLobby, "client.dll", "8B 89 ? ? ? ? 85 C9 74 ? 68 ? ? ? ? E8 ? ? ? ? 85 C0 74 ? 8B 48 ? 85 C9 74 ? 8B 40 ? 6A", 0x0);

//MAKE_SIGNATURE(CTFGCClientSystem_GetMatchInvite, "client.dll", "55 8B EC 83 EC ? 56 57 8B F9 8B 8F ? ? ? ? 85 C9 74 ? 68", 0x0);
//MAKE_SIGNATURE(CTFGCClientSystem_DumpLobby, "client.dll", "8B 0D ? ? ? ? 85 C9 74 ? 68 ? ? ? ? E8 ? ? ? ? 85 C0 74 ? 8B 48 ? 85 C9 74 ? 8B 40 ? 6A", 0x0);
//MAKE_SIGNATURE(CTFGCClientSystem_DumpParty, "client.dll", "8B 0D ? ? ? ? 85 C9 74 ? 68 ? ? ? ? E8 ? ? ? ? 85 C0 74 ? 8B 48 ? 85 C9 74 ? 8B 40 ? 8B 4C 88", 0x0);

MAKE_SIGNATURE(CTFGCClientSystem_GetParty, "client.dll", "48 83 EC ? 48 8B 89 ? ? ? ? 48 85 C9 74 ? BA ? ? ? ? E8 ? ? ? ? 48 85 C0 74 ? 8B 48 ? 85 C9 74 ? 48 8B 40 ? FF C9", 0x0);
MAKE_SIGNATURE(CTFGCClientSystem_JoinMMMatch, "client.dll", "48 89 5C 24 ? 57 48 83 EC ? 48 8B D9 48 81 C1 ? ? ? ? E8 ? ? ? ? 84 C0 0F 84", 0x0);
MAKE_SIGNATURE(CTFGCClientSystem_BLocalPlayerInventoryHasMvmTicket, "client.dll", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? E8 ? ? ? ? 48 8B C8 48 8B 10 FF 92 ? ? ? ? 48 8B F0 48 85 C0 0F 84 ? ? ? ? 8B 05 ? ? ? ? A8 ? 75 ? 83 C8 ? 48 8D 1D ? ? ? ? 89 05 ? ? ? ? 48 89 1D ? ? ? ? E8 ? ? ? ? 48 8B C8 48 8B D3 E8 ? ? ? ? 48 89 05 ? ? ? ? E8 ? ? ? ? 8B 48 ? 89 0D ? ? ? ? E8 ? ? ? ? 8B 58 ? 39 1D ? ? ? ? 74 ? E8 ? ? ? ? 48 8B 15 ? ? ? ? 48 8B C8 E8 ? ? ? ? 48 89 05 ? ? ? ? 89 1D ? ? ? ? EB ? 48 8B 05 ? ? ? ? 48 85 C0 74 ? 33 DB 39 5E ? 7E ? 8B C3 48 69 E8 ? ? ? ? 48 03 6E ? E8 ? ? ? ? 44 8B 70 ? 44 39 35 ? ? ? ? 74 ? E8 ? ? ? ? 48 8B 15 ? ? ? ? 48 8B C8 E8 ? ? ? ? 48 8B F8 48 89 05 ? ? ? ? 44 89 35 ? ? ? ? EB ? 48 8B 3D ? ? ? ? 48 8B 45 ? 48 8D 4D ? FF 50 ? 48 3B C7 74 ? FF C3 3B 5E ? 7C ? 32 C0 48 8B 5C 24 ? 48 8B 6C 24 ? 48 8B 74 24 ? 48 8B 7C 24 ? 48 83 C4 ? 41 5E C3 B0 ? EB ? CC CC CC CC CC CC CC CC 48 89 5C 24", 0x0);
MAKE_SIGNATURE(CTFGCClientSystem_BHasCompetitiveAccess, "client.dll", "48 83 EC ? E8 ? ? ? ? 48 8B C8 48 8B 10 FF 92 ? ? ? ? 48 85 C0 74 ? 48 8B 88 ? ? ? ? 48 85 C9 74 ? BA ? ? ? ? E8 ? ? ? ? 48 85 C0 74 ? 83 78 ? ? 75 ? 48 8B 40 ? 48 8B 08 48 85 C9 74 ? 8B 41 ? C1 E8 ? A8 ? 74 ? 80 79 ? ? 74 ? B0 ? 48 83 C4 ? C3 32 C0 48 83 C4 ? C3 CC CC CC CC CC CC CC CC CC CC CC 40 53", 0x0);
MAKE_SIGNATURE(CTFGCClientSystem_PingThink, "client.dll", "40 55 41 54 41 55 48 8D AC 24", 0x0);
MAKE_SIGNATURE(CTFGCClientSystem_UpdateAssignedLobby, "client.dll", "40 55 53 41 54 41 56 41 57 48 8B EC", 0x0);
MAKE_SIGNATURE(CTFGCClientSystem_AbandonCurrentMatch, "client.dll", "48 83 EC ? 48 89 5C 24 ? 48 8B D9 48 8D 0D ? ? ? ? 48 89 74 24", 0x0);
MAKE_SIGNATURE(CTFGCClientSystem_RequestAcceptMatchInvite, "client.dll", "41 55 41 56 48 83 EC ? 48 83 B9", 0x0);

MAKE_SIGNATURE(CTFParty_SpewDebug, "client.dll", "4C 8B DC 41 56 48 81 EC ? ? ? ? 8B 05", 0x0);

class CGCClientSharedObjectTypeCache
{
public:
	inline int GetCacheCount()
	{
		return *reinterpret_cast<int*>(uintptr_t(this) + 40);
	}
};

class CGCClientSharedObjectCache
{
public:
	SIGNATURE_ARGS(FindTypeCache, CGCClientSharedObjectTypeCache*, CGCClientSharedObjectCache, (int nClassID), this, nClassID);
};

struct CTFLobbyPlayerProto
{
	enum TF_GC_TEAM
	{
		TF_GC_TEAM_DEFENDERS = 0,
		TF_GC_TEAM_INVADERS = 1,
		TF_GC_TEAM_BROADCASTER = 2,
		TF_GC_TEAM_SPECTATOR = 3,
		TF_GC_TEAM_PLAYER_POOL = 4,
		TF_GC_TEAM_NOTEAM = 5
	};

	enum ConnectState
	{
		INVALID = 0,
		RESERVATION_PENDING = 1,
		RESERVED = 2,
		CONNECTED = 3,
		CONNECTED_AD_HOC = 4,
		DISCONNECTED = 5
	};

	enum Type {
		INVALID_PLAYER = 0,
		MATCH_PLAYER = 1,
		STANDBY_PLAYER = 2,
		OBSERVING_PLAYER = 3
	};

	byte pad0[24];
	uint64 id;
	TF_GC_TEAM team;
	ConnectState connect_state;
	const char* name;
	uint64 original_party_id;
	uint32 badge_level;
	uint32 last_connect_time;
	Type type;
	bool squad_surplus;
	bool chat_suspension;
	double normalized_rating;
	double normalized_uncertainty;
	uint32 rank;
};

class ConstTFLobbyPlayer
{
	void* pad0;
	void* pad1;

public:
	VIRTUAL(Proto, CTFLobbyPlayerProto*, 0, this);
};

class CTFLobbyShared
{
public:
	VIRTUAL(GetNumMembers, int, 2, this);
	VIRTUAL_ARGS(GetMember, CSteamID*, 3, (CSteamID* pSteamID, int i), this, pSteamID, i);
	VIRTUAL_ARGS(GetMemberIndexBySteamID, int, 4, (CSteamID& pSteamID), this, std::ref(pSteamID));
	VIRTUAL_ARGS(GetMemberDetails, ConstTFLobbyPlayer*, 13, (ConstTFLobbyPlayer* pDetails, int i), this, pDetails, i);
};

class CTFParty
{
public:
	VIRTUAL(GetNumMembers, int64, 2, uintptr_t(this) + 184);
	VIRTUAL_ARGS(GetMember, CSteamID*, 3, (CSteamID* pSteamID, int i), uintptr_t(this) + 184, pSteamID, i);

	SIGNATURE(SpewDebug, void, CTFParty, this);
};

class CTFGCClientSystem
{
public:
	SIGNATURE(PingThink, void, CTFGCClientSystem, this);
	SIGNATURE(GetParty, CTFParty*, CTFGCClientSystem, this);
	SIGNATURE(AbandonCurrentMatch, void, CTFGCClientSystem, this);
	SIGNATURE(JoinMMMatch, void, CTFGCClientSystem, this);
	SIGNATURE_ARGS(RequestAcceptMatchInvite, void, CTFGCClientSystem, (uint64 uGroupID), this, uGroupID);
	SIGNATURE(BHasCompetitiveAccess, bool, CTFGCClientSystem, this);
	SIGNATURE(BLocalPlayerInventoryHasMvmTicket, bool, CTFGCClientSystem, this);
	SIGNATURE(UpdateAssignedLobby, bool, CTFGCClientSystem, this);

	inline CGCClientSharedObjectCache* m_pSOCache()
	{
		return *reinterpret_cast<CGCClientSharedObjectCache**>(uintptr_t(this) + 1072);
	}

	inline CTFLobbyShared* GetLobby()
	{
		auto pSOCache = m_pSOCache();
		if (!pSOCache)
			return nullptr;

		auto pTypeCache = pSOCache->FindTypeCache(2004);
		if (!pTypeCache)
			return nullptr;

		int iCacheCount = pTypeCache->GetCacheCount();
		if (!iCacheCount)
			return nullptr;

		auto pLobby = *reinterpret_cast<CTFLobbyShared**>(*reinterpret_cast<uintptr_t*>(uintptr_t(pTypeCache) + 8) + 8 * uintptr_t(iCacheCount - 1));
		if (!pLobby)
			return nullptr;

		return reinterpret_cast<CTFLobbyShared*>(uintptr_t(pLobby) - 8); // i assume from the dynamic_cast?
	}

	inline void SetPendingPingRefresh(bool bValue)
	{
		*reinterpret_cast<bool*>(uintptr_t(this) + 1116) = bValue;
	}

	inline void SetNonPremiumAccount(bool bValue)
	{
		*reinterpret_cast<bool*>(uintptr_t(this) + 1888) = bValue;
	}
};

MAKE_INTERFACE_SIGNATURE(CTFGCClientSystem, TFGCClientSystem, "client.dll", "48 8D 05 ? ? ? ? C3 CC CC CC CC CC CC CC CC 48 8B 05 ? ? ? ? C3 CC CC CC CC CC CC CC CC 48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24", 0x0, 0);