#include "../SDK/SDK.h"

#include "../Features/Spectate/Spectate.h"

MAKE_SIGNATURE(CBasePlayer_ShouldDrawThisPlayer, "client.dll", "48 83 EC ? E8 ? ? ? ? 84 C0 74 ? 48 8B 0D ? ? ? ? 48 85 C9", 0x0);
MAKE_SIGNATURE(CBasePlayer_BuildFirstPersonMeathookTransformations_ShouldDrawThisPlayer_Call, "client.dll", "84 C0 0F 84 ? ? ? ? 48 8B 94 24 ? ? ? ? 48 8B CE", 0x0);

MAKE_HOOK(CBasePlayer_ShouldDrawThisPlayer, S::CBasePlayer_ShouldDrawThisPlayer(), bool, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CTFPlayer_ShouldDraw[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	static const auto dwUndesired = S::CBasePlayer_BuildFirstPersonMeathookTransformations_ShouldDrawThisPlayer_Call();
	const auto dwRetAddr = uintptr_t(_ReturnAddress());

	if (F::Spectate.m_iTarget != -1)
	{
		if (dwRetAddr == dwUndesired)
			return false;

		auto pLocal = H::Entities.GetLocal();
		auto pTarget = I::ClientEntityList->GetClientEntity(I::EngineClient->GetPlayerForUserID(F::Spectate.m_iTarget))->As<CTFPlayer>();

		if (pLocal && pLocal->IsAlive() && rcx == pLocal)
			return true;
		else if (pTarget && pTarget->IsAlive() && rcx == pTarget)
			return Vars::Visuals::Thirdperson::Enabled.Value;
	}

	return CALL_ORIGINAL(rcx);
}