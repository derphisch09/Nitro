#include "../SDK/SDK.h"
#include "../Features/Visuals/Materials/Materials.h"

MAKE_SIGNATURE(CBaseClient_Connect, "engine.dll", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B D9 49 8B E9 48 8D 0D", 0x0);
//MAKE_SIGNATURE(CBaseClient_Connect, "engine.dll", "E8 ? ? ? ? 8B 4E 14", 0x0);

MAKE_HOOK(CBaseClient_Connect, S::CBaseClient_Connect(), void, void* rcx, const char* szName, int nUserID, INetChannel* pNetChannel, bool bFakePlayer, int clientChallenge)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CBaseClient_Connect[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, szName, nUserID, pNetChannel, bFakePlayer, clientChallenge);
#endif

	F::Materials.ReloadMaterials();
	CALL_ORIGINAL(rcx, szName, nUserID, pNetChannel, bFakePlayer, clientChallenge);
}