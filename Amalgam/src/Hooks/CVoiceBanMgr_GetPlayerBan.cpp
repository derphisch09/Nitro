#include "../SDK/SDK.h"

MAKE_SIGNATURE(CVoiceBanMgr_GetPlayerBan, "client.dll", "55 8B EC FF 75 ? E8 ? ? ? ? 85 C0 0F 95 C0 5D C2 ? ? CC CC CC CC CC CC CC CC CC CC CC CC 55 8B EC 83 EC", 0x0);

MAKE_HOOK(CVoiceBanMgr_GetPlayerBan, S::CVoiceBanMgr_GetPlayerBan(), bool, void* rcx, char const playerID[SIGNED_GUID_LEN])
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CVoiceBanMgr_GetPlayerBan[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, playerID);
#endif

	const bool bReturn = CALL_ORIGINAL(rcx, playerID);
	SDK::Output("CVoiceBanMgr_GetPlayerBan", std::format("%s is%s voice-banned.", playerID, (bReturn ? "" : " not")).c_str(), {118, 116, 107, 255});
	return bReturn;
}