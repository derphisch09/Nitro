#include "../SDK/SDK.h"

#include "../Features/Players/PlayerUtils.h"

MAKE_SIGNATURE(CTFMatchSummary_UpdatePlayerAvatar, "client.dll", "40 55 41 57 48 83 EC ? 48 8B E9 4D 8B F8", 0x0);

MAKE_HOOK(CTFMatchSummary_UpdatePlayerAvatar, S::CTFMatchSummary_UpdatePlayerAvatar(), void, void* rcx, int playerIndex, KeyValues* kv)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CTFClientScoreBoardDialog_UpdatePlayerAvatar[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, playerIndex, kv);
#endif

	int iType = 0; F::PlayerUtils.GetPlayerName(playerIndex, nullptr, &iType);

	if (iType != 1)
		CALL_ORIGINAL(rcx, playerIndex, kv);
}