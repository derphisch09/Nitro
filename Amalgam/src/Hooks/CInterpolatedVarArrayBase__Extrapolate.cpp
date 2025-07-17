#include "../SDK/SDK.h"

MAKE_SIGNATURE(CInterpolatedVarArrayBase__Extrapolate, "client.dll", "55 8B EC 8B 45 0C 8B D1 F3 0F 10 05 ? ? ? ? 56", 0x0);

MAKE_HOOK(CInterpolatedVarArrayBase__Extrapolate, S::CInterpolatedVarArrayBase__Extrapolate(), void, void* rcx, void* pOut, void* pOld, void* pNew, float flDestinationTime, float flMaxExtrapolationAmount)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CInterpolatedVarArrayBase__Extrapolate[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, pOut, pOld, pNew, flDestinationTime, flMaxExtrapolationAmount);
#endif

	return CALL_ORIGINAL(rcx, pOut, pOld, pNew, flDestinationTime, flMaxExtrapolationAmount);
}