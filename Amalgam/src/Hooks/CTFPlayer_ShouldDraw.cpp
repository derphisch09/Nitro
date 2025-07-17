#include "../SDK/SDK.h"

#include "../Features/Spectate/Spectate.h"

MAKE_SIGNATURE(CTFPlayer_ShouldDraw, "client.dll", "48 89 74 24 ? 57 48 83 EC ? 48 8D 71", 0x0);

MAKE_HOOK(CTFPlayer_ShouldDraw, S::CTFPlayer_ShouldDraw(), bool, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CTFPlayer_ShouldDraw[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	if (F::Spectate.m_iTarget != -1)
	{
		auto pLocal = H::Entities.GetLocal();
		auto pTarget = I::ClientEntityList->GetClientEntity(I::EngineClient->GetPlayerForUserID(F::Spectate.m_iTarget))->As<CTFPlayer>();
		
		if (pLocal && pLocal->IsAlive() && rcx == pLocal->GetClientRenderable())
			return true;
		else if (pTarget && pTarget->IsAlive() && rcx == pTarget->GetClientRenderable())
			return Vars::Visuals::Thirdperson::Enabled.Value;
	}

	return CALL_ORIGINAL(rcx);
}