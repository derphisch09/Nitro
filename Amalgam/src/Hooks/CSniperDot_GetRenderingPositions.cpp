#include "../SDK/SDK.h"

MAKE_SIGNATURE(CSniperDot_GetRenderingPositions, "client.dll", "48 89 5C 24 ? 48 89 74 24 ? 55 57 41 57 48 8D 6C 24", 0x0);

MAKE_HOOK(CSniperDot_GetRenderingPositions, S::CSniperDot_GetRenderingPositions(), bool, void* rcx, CTFPlayer* pPlayer, Vec3& vecAttachment, Vec3& vecEndPos, float& flSize)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CSniperDot_GetRenderingPositions[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, pPlayer, vecAttachment, vecEndPos, flSize);
#endif

	if (pPlayer && pPlayer->entindex() != I::EngineClient->GetLocalPlayer())
	{
		auto pDot = reinterpret_cast<CSniperDot*>(rcx);

<<<<<<< Updated upstream
		vEyePosition = pPlayer->m_vecOrigin() + pPlayer->GetViewOffset();
		vEyeAngles = Math::VectorAngles(pDot->GetAbsOrigin() - vEyePosition);
=======
		G::EyePosition = pPlayer->m_vecOrigin() + pPlayer->GetViewOffset();
		Math::VectorAngles(pDot->GetAbsOrigin() - G::EyePosition, G::EyeAngles);
>>>>>>> Stashed changes
	}

	return CALL_ORIGINAL(rcx, pPlayer, vecAttachment, vecEndPos, flSize);
}