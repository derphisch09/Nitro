#include "../SDK/SDK.h"

MAKE_SIGNATURE(CPlayerMove_RunCommand, "server.dll", "48 89 5C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC ? 8B 9A", 0x0);

static std::unordered_map<int, int> mTickStorage = {};

MAKE_HOOK(CPlayerMove_RunCommand, S::CPlayerMove_RunCommand(), void, void* rcx, CBasePlayer* player, CUserCmd* ucmd, IMoveHelper* moveHelper)
{
	if (G::TickInfo)
	{
		int nTicks = player->m_nMovementTicksForUserCmdProcessingRemaining() - 1;
		int iIndex = player->entindex();

		if (nTicks != mTickStorage[iIndex])
		{
			mTickStorage[iIndex] = nTicks;
			SDK::OutputClient("Ticks", std::format("{}", nTicks).c_str(), player, HUD_PRINTTALK);
		}
	}

	CALL_ORIGINAL(rcx, player, ucmd, moveHelper);
}