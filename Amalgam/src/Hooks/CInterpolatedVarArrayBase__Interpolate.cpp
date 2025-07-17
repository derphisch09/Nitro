#include "../SDK/SDK.h"

MAKE_SIGNATURE(CInterpolatedVarArrayBase__Interpolate, "client.dll", "55 8B EC 8B 45 14 33 D2 56 8B F1 8B 4D 10 57 3B C8 75 28 38 56 1D 0F 86 ? ? ? ? 8B 78 08 8B 4D 08 2B F9 D9 04 0F 42 D9 19 0F B6 46 1D 83 C1 04 3B D0 7C EF 5F 5E", 0x0);

MAKE_HOOK(CInterpolatedVarArrayBase__Interpolate, S::CInterpolatedVarArrayBase__Interpolate(), void, void* rcx, void* out, float frac, void* start, void* end)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CInterpolatedVarArrayBase__Interpolate[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, out, frac, start, end);
#endif

	return CALL_ORIGINAL(rcx, out, frac, start, end);
}