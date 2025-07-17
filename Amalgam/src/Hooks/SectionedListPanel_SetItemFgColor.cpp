#include "../SDK/SDK.h"

MAKE_SIGNATURE(SectionedListPanel_SetItemFgColor, "client.dll", "40 53 48 83 EC ? 48 8B D9 3B 91 ? ? ? ? 73 ? 3B 91 ? ? ? ? 7F ? 48 8B 89 ? ? ? ? 48 89 7C 24 ? 8B FA 48 03 FF 39 54 F9 ? 75 ? 39 54 F9 ? 75 ? 48 8B 0C F9 41 8B D0 48 8B 01 FF 90 ? ? ? ? 48 8B 83 ? ? ? ? B2 ? 48 8B 0C F8 48 8B 01 FF 90 ? ? ? ? 48 8B 83 ? ? ? ? 45 33 C0", 0x0);
MAKE_SIGNATURE(CTFClientScoreBoardDialog_UpdatePlayerList_SetItemFgColor_Call, "client.dll", "49 8B 04 24 8B D5 C7 44 24", 0x0);

MAKE_HOOK(SectionedListPanel_SetItemFgColor, S::SectionedListPanel_SetItemFgColor(), void, void* rcx, int itemID, Color_t color)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CTFClientScoreBoardDialog_UpdatePlayerAvatar[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, itemID, color);
#endif

	static const auto dwDesired = S::CTFClientScoreBoardDialog_UpdatePlayerList_SetItemFgColor_Call();
	const auto dwRetAddr = uintptr_t(_ReturnAddress());

	if (dwDesired == dwRetAddr && Vars::Visuals::UI::ScoreboardColors.Value)
	{
		Color_t tColor = H::Color.GetScoreboardColor(G::PlayerIndex);

		if (tColor.a)
		{
			auto pResource = H::Entities.GetPR();

			if (pResource && !pResource->m_bAlive(G::PlayerIndex))
				tColor = tColor.Lerp({ 127, 127, 127, tColor.a }, 0.5f);

			color = tColor;
		}
	}

	CALL_ORIGINAL(rcx, itemID, color);
}