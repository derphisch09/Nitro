#include "../SDK/SDK.h"

std::hash<std::string_view> mHash;

MAKE_SIGNATURE(CBaseEntity_AddVar, "engine.dll", "55 8B EC 83 EC 10 8B 45 08 53 8B D9 C7 45 ? ? ? ? ? 83 78 20 00 0F 8E ? ? ? ? 33 D2 56 89 55 F8 57", 0x0);

MAKE_HOOK(CBaseEntity_AddVar, S::CBaseEntity_AddVar(), void, void* rcx, void* data, IInterpolatedVar* watcher, int type, bool bSetup)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CBaseEntity_AddVar[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, data, watcher, type, bSetup);
#endif

	if (watcher && Vars::Visuals::Removals::Interpolation.Value)
	{
		const size_t hash = mHash(watcher->GetDebugName());

		static const size_t m_vecVelocity = mHash("CBasePlayer::m_vecVelocity");
		static const size_t m_angEyeAngles = mHash("CTFPlayer::m_angEyeAngles");
		static const size_t m_flPoseParameter = mHash("CBaseAnimating::m_flPoseParameter");
		static const size_t m_flCycle = mHash("CBaseAnimating::m_flCycle");
		static const size_t m_flMaxGroundSpeed = mHash("CMultiPlayerAnimState::m_flMaxGroundSpeed");

		if (hash == m_vecVelocity || hash == m_flPoseParameter || hash == m_flCycle || hash == m_flMaxGroundSpeed || (hash == m_angEyeAngles && rcx == H::Entities.GetLocal()))
		{
			return;
		}
	}

	return CALL_ORIGINAL(rcx, data, watcher, type, bSetup);
}