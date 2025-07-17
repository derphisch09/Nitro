#include "../SDK/SDK.h"

MAKE_SIGNATURE(CTFPlayer_EyeAngles, "client.dll", "40 53 48 83 EC ? 48 8B D9 E8 ? ? ? ? 84 C0 74 ? 83 3D", 0x0);
MAKE_SIGNATURE(CSniperDot_GetRenderingPositions_EyeAngles_Call, "client.dll", "48 8D 54 24 ? 48 8D 4C 24 ? F2 0F 10 00 F2 0F 11 44 24 ? 8B 40 ? 89 44 24 ? E8 ? ? ? ? 49 8B 07", 0x0);

MAKE_HOOK(CTFPlayer_EyeAngles, S::CTFPlayer_EyeAngles(), Vec3*, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CSniperDot_GetRenderingPositions[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	static const auto dwDesired = S::CSniperDot_GetRenderingPositions_EyeAngles_Call();
	const auto dwRetAddr = uintptr_t(_ReturnAddress());

	if (dwRetAddr == dwDesired)
		return &G::EyeAngles;

	return CALL_ORIGINAL(rcx);
}