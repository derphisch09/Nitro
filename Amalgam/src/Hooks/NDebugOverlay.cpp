#include "../SDK/SDK.h"

MAKE_SIGNATURE(NDebugOverlay_BoxAngles, "server.dll", "48 83 EC ? 4C 8B D9 48 8B 0D ? ? ? ? 48 85 C9 74 ? 8B 84 24 ? ? ? ? F3 0F 10 84 24 ? ? ? ? 4C 8B 11 F3 0F 11 44 24 ? 89 44 24 ? 8B 84 24 ? ? ? ? 89 44 24 ? 8B 84 24 ? ? ? ? 89 44 24 ? 8B 84 24 ? ? ? ? 89 44 24 ? 4C 89 4C 24", 0x0);
MAKE_SIGNATURE(CBaseAnimating_DrawServerHitboxes_BoxAngles_Call, "server.dll", "8B 84 24 ? ? ? ? 49 83 C6", 0x0);

MAKE_HOOK(NDebugOverlay_BoxAngles, S::NDebugOverlay_BoxAngles(), void, Vector& origin, Vector& mins, Vector& maxs, QAngle& angles, int r, int g, int b, int a, float duration)
{
	if (G::DrawHeadOnly)
	{
		static const auto dwDesired = S::CBaseAnimating_DrawServerHitboxes_BoxAngles_Call();
		const auto dwRetAddr = uintptr_t(_ReturnAddress());

		if (dwRetAddr == dwDesired && (r != 255 || g != 127 || b != 127))
			return;
	}

	if (G::NoBoxAngles)
		angles = {};

	SDK::OutputClient("BoxAngles", std::format("{} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {}", origin.x, origin.y, origin.z, mins.x, mins.y, mins.z, maxs.x, maxs.y, maxs.z, angles.x, angles.y, angles.z, r, g, b, a, duration).c_str(), G::DebugTarget);
	CALL_ORIGINAL(origin, mins, maxs, angles, r, g, b, a, duration);
}