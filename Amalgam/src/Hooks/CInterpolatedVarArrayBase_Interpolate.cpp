#include "../SDK/SDK.h"

MAKE_SIGNATURE(CInterpolatedVarArrayBase_Interpolate, "client.dll", "48 8B C4 55 56 57 48 8D 68 ? 48 81 EC ? ? ? ? 0F 29 78", 0x0);

MAKE_HOOK(CInterpolatedVarArrayBase_Interpolate, S::CInterpolatedVarArrayBase_Interpolate(), int, void* rcx, float currentTime, float interpolation_amount)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CInterpolatedVarArrayBase_Interpolate[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, currentTime, interpolation_amount);
#endif

	return Vars::Visuals::Removals::Interpolation.Value ? 1 : CALL_ORIGINAL(rcx, currentTime, interpolation_amount);
}