#include "../SDK/SDK.h"

MAKE_SIGNATURE(CClientScoreBoardDialog_UpdatePlayerAvatar, "client.dll", "4D 85 C0 0F 84 ? ? ? ? 53 55", 0x0);

MAKE_HOOK(CClientScoreBoardDialog_UpdatePlayerAvatar, S::CClientScoreBoardDialog_UpdatePlayerAvatar(), void, void* rcx, int playerIndex, KeyValues* kv)
{
	if (Vars::Visuals::UI::StreamerMode.Value)
		return;

	CALL_ORIGINAL(rcx, playerIndex, kv); 
}