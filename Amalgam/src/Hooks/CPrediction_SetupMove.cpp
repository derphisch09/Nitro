#include "../SDK/SDK.h"

MAKE_HOOK(CPrediction_SetupMove, U::Memory.GetVirtual(I::Prediction, 18), void, void* rcx, CBasePlayer* player, CUserCmd* cmd, IMoveHelper* moveHelper, CMoveData* move)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CPrediction_FinishMove[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, player, cmd, moveHelper, move);
#endif

	CALL_ORIGINAL(rcx, player, cmd, moveHelper, move);
}