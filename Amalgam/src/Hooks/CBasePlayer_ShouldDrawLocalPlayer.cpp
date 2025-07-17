#include "../SDK/SDK.h"

#include "../Features/Spectate/Spectate.h"

MAKE_SIGNATURE(CBasePlayer_ShouldDrawLocalPlayer, "client.dll", "48 83 EC ? 48 8B 0D ? ? ? ? 48 85 C9 74 ? 48 8B 01 FF 50 ? 84 C0 74 ? 8B 05", 0x0);

MAKE_HOOK(CBasePlayer_ShouldDrawLocalPlayer, S::CBasePlayer_ShouldDrawLocalPlayer(), bool, /*void* rcx*/)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CTFPlayer_ShouldDraw[DEFAULT_BIND])
		return CALL_ORIGINAL(/*rcx*/);
#endif

	if (F::Spectate.m_iTarget != -1)
	{
		auto pLocal = H::Entities.GetLocal();

		if (pLocal && pLocal->IsAlive())
			return true;
	}

	return CALL_ORIGINAL(/*rcx*/);
}