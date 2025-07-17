#include "../SDK/SDK.h"

MAKE_HOOK(CPrediction_FinishMove, U::Memory.GetVirtual(I::Prediction, 19), void, void* rcx, CBasePlayer* player, CUserCmd* cmd, CMoveData* move)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CPrediction_FinishMove[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, player, cmd, move);
#endif

	float pitch = move->m_vecAngles.x;

	if (pitch > 180.0f)
		pitch -= 360.0f;

	pitch = std::clamp(pitch, -90.0f, 90.0f);
	move->m_vecAngles.x = pitch;
	player->SetLocalAngles(move->m_vecAngles);

	CALL_ORIGINAL(rcx, player, cmd, move);
}