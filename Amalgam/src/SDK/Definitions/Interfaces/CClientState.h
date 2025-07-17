#pragma once
#include "Interface.h"
#include "../Main/INetChannel.h"
#include "../Misc/ClientClass.h"
#include "../Misc/ServerClass.h"
#include "../Definitions.h"

MAKE_SIGNATURE(CClientState_IsPaused, "engine.dll", "48 83 EC ? 80 B9 ? ? ? ? ? 75", 0x0);
MAKE_SIGNATURE(CClientState_SendStringCmd, "engine.dll", "48 81 EC ? ? ? ? 48 8B 49", 0x0);
MAKE_SIGNATURE(CClientState_ForceFullUpdate, "engine.dll", "40 53 48 83 EC ? 83 B9 ? ? ? ? ? 48 8B D9 74 ? E8", 0x0);
//MAKE_SIGNATURE(CClientState_GetClientInterpAmount, "engine.dll", "E8 ? ? ? ? F3 0F 58 F8", 0x0);

class IChangeFrameList;

class PackedEntity
{
public:
	ServerClass* m_pServerClass;
	ClientClass* m_pClientClass;

	int m_nEntityIndex;
	int m_ReferenceCount;

private:
	CUtlVector<CSendProxyRecipients> m_Recipients;

	void* m_pData;
	int m_nBits;
	IChangeFrameList* m_pChangeFrameList;

	unsigned int m_nSnapshotCreationTick : 31;
	unsigned int m_nShouldCheckCreationTick : 1;
};

struct CClockDriftMgr
{
	float m_ClockOffsets[16];
	int m_iCurClockOffset;
	int m_nServerTick;
	int m_nClientTick;
};

class CClientState
{
public:
	byte pad0[24];
	int m_Socket;
	INetChannel* m_NetChannel;
	unsigned int m_nChallengeNr;
	double m_flConnectTime;
	int m_nRetryNumber;
	char m_szRetryAddress[MAX_OSPATH];
	CUtlString m_sRetrySourceTag;
	int m_retryChallenge;
	int m_nSignonState;
	double m_flNextCmdTime;
	int m_nServerCount;
	unsigned __int64 m_ulGameServerSteamID;
	int m_nCurrentSequence;
	CClockDriftMgr m_ClockDriftMgr;
	int m_nDeltaTick;
	bool m_bPaused;
	float m_flPausedExpireTime;
	int m_nViewEntity;
	int m_nPlayerSlot;
	char m_szLevelFileName[128];
	byte pad1[132];
	char m_szLevelBaseName[128];
	byte pad2[132];
	int m_nMaxClients;
	PackedEntity* m_pEntityBaselines[2][MAX_EDICTS];
	byte pad3[2068];
	void* m_StringTableContainer;
	bool m_bRestrictServerCommands;
	bool m_bRestrictClientCommands;
	byte pad4[106];
	bool insimulation;
	int oldtickcount;
	float m_tickRemainder;
	float m_frameTime;
	int lastoutgoingcommand;
	int chokedcommands;
	int last_command_ack;
	int command_ack;
	int m_nSoundSequence;
	bool ishltv;
	bool isreplay;
	byte pad5[278];
	int demonum;
	CUtlString demos[32];
	byte pad6[344184];
	bool m_bMarkedCRCsUnverified;

public:
	inline bool IsConnected() const
	{
		return m_nSignonState >= SIGNONSTATE_CONNECTED;
	}

	inline bool IsActive() const
	{
		return m_nSignonState == SIGNONSTATE_FULL;
	}

	SIGNATURE(IsPaused, bool, CClientState, this);
	SIGNATURE_ARGS(SendStringCmd, void, CClientState, (const char* command), this, command);
	SIGNATURE(ForceFullUpdate, void, CClientState, this);
	//SIGNATURE(GetClientInterpAmount, float, CClientState, this);
};

MAKE_INTERFACE_SIGNATURE(CClientState, ClientState, "engine.dll", "48 8D 0D ? ? ? ? E8 ? ? ? ? F3 0F 5E 05", 0x0, 0);