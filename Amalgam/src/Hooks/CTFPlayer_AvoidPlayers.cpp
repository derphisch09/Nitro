#include "../SDK/SDK.h"

MAKE_SIGNATURE(CTFPlayer_AvoidPlayers, "client.dll", "48 89 54 24 ? 55 41 56", 0x0);

MAKE_HOOK(CTFPlayer_AvoidPlayers, S::CTFPlayer_AvoidPlayers(), void, void* rcx, CUserCmd* pCmd)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CTFPlayer_AvoidPlayers[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, pCmd);
#endif

	//if (Vars::Misc::Movement::NoPush.Value)
		//return;

	switch (Vars::Misc::Movement::NoPush.Value)
	{
	case Vars::Misc::Movement::NoPushEnum::Off:
		break;
	case Vars::Misc::Movement::NoPushEnum::Always:
		return;
	case Vars::Misc::Movement::NoPushEnum::WhileMoving:
	{
		if (pCmd->buttons & (IN_FORWARD | IN_BACK | IN_MOVERIGHT | IN_MOVELEFT))
			return;

		break;
	}
	case Vars::Misc::Movement::NoPushEnum::PartialWhileAFK:
	{
		if (pCmd->buttons & (IN_FORWARD | IN_BACK | IN_MOVERIGHT | IN_MOVELEFT))
			return;

		std::pair<float, float> oldMoves = { pCmd->forwardmove, pCmd->sidemove };
		CALL_ORIGINAL(rcx, pCmd);

		pCmd->forwardmove += oldMoves.first; pCmd->forwardmove /= 3;
		pCmd->sidemove += oldMoves.second; pCmd->sidemove /= 3;

		return;
	}
	}

	CALL_ORIGINAL(rcx, pCmd);
}