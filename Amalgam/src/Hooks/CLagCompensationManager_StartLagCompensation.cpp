#include "../SDK/SDK.h"

MAKE_SIGNATURE(CLagCompensationManager_StartLagCompensation, "server.dll", "55 8B EC 83 EC ? 57 8B F9 89 7D ? 83 BF", 0x0);

MAKE_HOOK(CLagCompensationManager_StartLagCompensation, S::CLagCompensationManager_StartLagCompensation(), void, void* rcx, int player, CUserCmd* pCmd)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CLagCompensationManager_StartLagCompensation[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, player, pCmd);
#endif

	const float flLerpTime = (*(float*)((DWORD)player + 2756));
	SDK::Output("CLagCompensationManager_StartLagCompensation", std::format("flLerpTime = %.3f", flLerpTime).c_str(), { 0, 222, 255, 255 });

	return CALL_ORIGINAL(rcx, player, pCmd);
}