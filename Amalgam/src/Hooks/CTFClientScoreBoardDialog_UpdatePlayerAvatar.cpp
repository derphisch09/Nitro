#include "../SDK/SDK.h"

#include "../Features/Players/PlayerUtils.h"

MAKE_SIGNATURE(CTFClientScoreBoardDialog_UpdatePlayerAvatar, "client.dll", "4D 85 C0 0F 84 ? ? ? ? 53 41 54 41 57", 0x0);

<<<<<<< Updated upstream
static int iPlayerIndex;

MAKE_HOOK(CTFClientScoreBoardDialog_UpdatePlayerAvatar, S::CTFClientScoreBoardDialog_UpdatePlayerAvatar(), void,
	void* rcx, int playerIndex, KeyValues* kv)
=======
MAKE_HOOK(CTFClientScoreBoardDialog_UpdatePlayerAvatar, S::CTFClientScoreBoardDialog_UpdatePlayerAvatar(), void, void* rcx, int playerIndex, KeyValues* kv)
>>>>>>> Stashed changes
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CTFClientScoreBoardDialog_UpdatePlayerAvatar[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, playerIndex, kv);
#endif

<<<<<<< Updated upstream
	iPlayerIndex = playerIndex;
=======
	G::PlayerIndex = playerIndex;
>>>>>>> Stashed changes

	int iType = 0; F::PlayerUtils.GetPlayerName(playerIndex, nullptr, &iType);

	if (iType != 1)
		CALL_ORIGINAL(rcx, playerIndex, kv);
<<<<<<< Updated upstream
}

MAKE_HOOK(CTFMatchSummary_UpdatePlayerAvatar, S::CTFMatchSummary_UpdatePlayerAvatar(), void,
	void* rcx, int playerIndex, KeyValues* kv)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CTFClientScoreBoardDialog_UpdatePlayerAvatar[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, playerIndex, kv);
#endif

	int iType = 0; F::PlayerUtils.GetPlayerName(playerIndex, nullptr, &iType);
	if (iType != 1)
		CALL_ORIGINAL(rcx, playerIndex, kv);
}

MAKE_HOOK(CTFHudMannVsMachineScoreboard_UpdatePlayerAvatar, S::CTFHudMannVsMachineScoreboard_UpdatePlayerAvatar(), void,
	void* rcx, int playerIndex, KeyValues* kv)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CTFClientScoreBoardDialog_UpdatePlayerAvatar[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, playerIndex, kv);
#endif

	int iType = 0; F::PlayerUtils.GetPlayerName(playerIndex, nullptr, &iType);
	if (iType != 1)
		CALL_ORIGINAL(rcx, playerIndex, kv);
}

MAKE_HOOK(CTFHudMatchStatus_UpdatePlayerAvatar, S::CTFHudMatchStatus_UpdatePlayerAvatar(), void,
	void* rcx, int playerIndex, KeyValues* kv)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CTFClientScoreBoardDialog_UpdatePlayerAvatar[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, playerIndex, kv);
#endif

	int iType = 0; F::PlayerUtils.GetPlayerName(playerIndex, nullptr, &iType);
	if (iType != 1)
		CALL_ORIGINAL(rcx, playerIndex, kv);
}

MAKE_HOOK(SectionedListPanel_SetItemFgColor, S::SectionedListPanel_SetItemFgColor(), void,
	void* rcx, int itemID, Color_t color)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CTFClientScoreBoardDialog_UpdatePlayerAvatar[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, itemID, color);
#endif

	static const auto dwDesired = S::CTFClientScoreBoardDialog_UpdatePlayerList_SetItemFgColor_Call();
	const auto dwRetAddr = uintptr_t(_ReturnAddress());

	if (dwDesired == dwRetAddr && Vars::Visuals::UI::ScoreboardColors.Value)
	{
		Color_t tColor = H::Color.GetScoreboardColor(iPlayerIndex);
		if (tColor.a)
		{
			auto pResource = H::Entities.GetPR();
			if (pResource && !pResource->m_bAlive(iPlayerIndex))
				tColor = tColor.Lerp({ 127, 127, 127, tColor.a }, 0.5f);

			color = tColor;
		}
	}

	CALL_ORIGINAL(rcx, itemID, color);
=======
>>>>>>> Stashed changes
}