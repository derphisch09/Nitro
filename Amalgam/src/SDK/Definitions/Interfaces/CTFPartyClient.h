#pragma once
#include "Interface.h"

//MAKE_SIGNATURE(CTFPartyClient_BInStandbyQueue, "client.dll", "8A 41 ? C3 CC CC CC CC CC CC CC CC CC CC CC CC 55 8B EC 81 EC ? ? ? ? 56", 0x0);
//MAKE_SIGNATURE(CTFPartyClient_BCanQueueForMatch, "client.dll", "55 8B EC 81 EC ? ? ? ? 8B 45 ? 89 45 ? 8D 45", 0x0);
//MAKE_SIGNATURE(CTFPartyClient_BCanQueueForStandby, "client.dll", "55 8B EC 83 EC ? 56 6A ? 8B F1 E8 ? ? ? ? 84 C0", 0x0);

//MAKE_SIGNATURE(CTFPartyClient_BMakeUpdateMsg, "client.dll", "55 8B EC 83 EC ? 53 56 8B F1 33 C9 8B 86", 0x0);
//MAKE_SIGNATURE(CTFPartyClient_CancelOutgoingJoinRequestOrIncomingInvite, "client.dll", "55 8B EC 83 EC ? 56 8B F1 83 7E ? ? 74 ? 80 7E", 0x0);
//MAKE_SIGNATURE(CTFPartyClient_CheckResetSentOptions, "client.dll", "55 8B EC 83 EC ? A1 ? ? ? ? 53 56 57 83 78 ? ? 8B D9", 0x0);
//MAKE_SIGNATURE(CTFPartyClient_OnInQueueChanged, "client.dll", "55 8B EC 56 8B 75 ? 57 56 8B F9 E8 ? ? ? ? 83 C4 ? 84 C0 74 ? 83 FE ? 74 ? 8B 57 ? 33 C0 85 D2 7E ? 8B 4F ? 39 31 74 ? 40 83 C1 ? 3B C2 7C ? 83 C8 ? 83 F8 ? 0F 95 C0", 0x0);
//MAKE_SIGNATURE(CTFPartyClient_RequestQueueForStandby, "client.dll", "55 8B EC 83 EC ? 56 8B F1 83 7E ? ? 0F 84 ? ? ? ? 80 BE", 0x0);

//MAKE_SIGNATURE(CTFPartyClient_UpdateActiveParty, "client.dll", "55 8B EC 81 EC ? ? ? ? 8B 15 ? ? ? ? 53 56 57 33 FF 8B F1", 0x0);

MAKE_SIGNATURE(CTFPartyClient_SendPartyChat, "client.dll", "48 89 5C 24 ? 48 89 6C 24 ? 57 48 83 EC ? 48 C7 C3", 0x0);
MAKE_SIGNATURE(CTFPartyClient_LoadSavedCasualCriteria, "client.dll", "48 83 79 ? ? C6 81 ? ? ? ? ? 74 ? 80 79 ? ? 74 ? C6 81 ? ? ? ? ? 48 8B 15", 0x0);
MAKE_SIGNATURE(CTFPartyClient_BInQueueForMatchGroup, "client.dll", "48 89 5C 24 ? 57 48 83 EC ? 48 8B F9 8B DA 8B CA E8 ? ? ? ? 84 C0", 0x0);
MAKE_SIGNATURE(CTFPartyClient_RequestQueueForMatch, "client.dll", "40 55 56 48 81 EC ? ? ? ? 48 63 F2", 0x0);

class CTFPartyClient
{
public:
	SIGNATURE_ARGS(SendPartyChat, void, CTFPartyClient, (const char* sMessage), this, sMessage);
	SIGNATURE(LoadSavedCasualCriteria, void, CTFPartyClient, this);
	SIGNATURE_ARGS(BInQueueForMatchGroup, bool, CTFPartyClient, (int eMatchGroup), this, eMatchGroup);
	SIGNATURE_ARGS(RequestQueueForMatch, void, CTFPartyClient, (int eMatchGroup), this, eMatchGroup);
};

MAKE_INTERFACE_NULL(CTFPartyClient, TFPartyClient);