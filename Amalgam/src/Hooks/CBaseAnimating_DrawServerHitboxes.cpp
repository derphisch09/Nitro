#include "../SDK/SDK.h"

MAKE_HOOK(CBaseAnimating_DrawServerHitboxes, S::CBaseAnimating_DrawServerHitboxes(), void, void* rcx, float duration, bool monocolor)
{
	auto pEntity = reinterpret_cast<CBaseAnimating*>(rcx);

	if (G::DebugTarget && G::DrawBoundingBox && pEntity->IsPlayer())
	{
		Vec3 origin = pEntity->m_vecOrigin();
		Vec3 mins = pEntity->m_vecMins();
		Vec3 maxs = pEntity->m_vecMaxs();
		Vec3 angles = {};
		int r = 255, g = 127, b = 127, a = 0;

		SDK::OutputClient("BoxAngles", std::format("{} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {}", origin.x, origin.y, origin.z, mins.x, mins.y, mins.z, maxs.x, maxs.y, maxs.z, angles.x, angles.y, angles.z, r, g, b, a, duration).c_str(), G::DebugTarget);
	}

	if (G::DrawHeadOnly)
		monocolor = false;

	CALL_ORIGINAL(rcx, duration, monocolor);
}