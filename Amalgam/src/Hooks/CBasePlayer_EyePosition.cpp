#include "../SDK/SDK.h"

MAKE_SIGNATURE(CBasePlayer_EyePosition, "client.dll", "48 89 5C 24 ? 57 48 83 EC ? 44 8B 81 ? ? ? ? 48 8B FA", 0x0);
MAKE_SIGNATURE(CSniperDot_GetRenderingPositions_EyePosition_Call, "client.dll", "8B 08 89 0F 8B 48 ? 89 4F ? 49 8B CF", 0x0);

MAKE_HOOK(CBasePlayer_EyePosition, S::CBasePlayer_EyePosition(), Vec3*, void* rcx, void* rdx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CSniperDot_GetRenderingPositions[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, rdx);
#endif

	static const auto dwDesired = S::CSniperDot_GetRenderingPositions_EyePosition_Call();
	const auto dwRetAddr = uintptr_t(_ReturnAddress());

	if (dwRetAddr == dwDesired)
		return &G::EyePosition;

	return CALL_ORIGINAL(rcx, rdx);
}