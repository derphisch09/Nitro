#include "../SDK/SDK.h"

MAKE_SIGNATURE(CTFInput_CAM_CapYaw, "client.dll", "40 53 48 83 EC ? 0F 29 74 24 ? 0F 28 F1", 0x0);

MAKE_HOOK(CTFInput_CAM_CapYaw, S::CTFInput_CAM_CapYaw(), float, void* rcx, float fVal)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CTFInput_CAM_CapYaw[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, fVal);
#endif

	if (!Vars::Misc::Movement::ShieldTurnRate.Value)
		return CALL_ORIGINAL(rcx, fVal);

	return fVal;
}