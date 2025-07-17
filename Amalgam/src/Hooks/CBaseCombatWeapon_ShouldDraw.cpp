#include "../SDK/SDK.h"

#include "../Features/Spectate/Spectate.h"

MAKE_SIGNATURE(CBaseCombatWeapon_ShouldDraw, "client.dll", "48 89 5C 24 ? 57 48 83 EC ? 83 B9 ? ? ? ? ? 48 8B D9 74 ? 8B 81", 0x0);

MAKE_HOOK(CBaseCombatWeapon_ShouldDraw, S::CBaseCombatWeapon_ShouldDraw(), bool, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CTFPlayer_ShouldDraw[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	if (F::Spectate.m_iTarget != -1)
	{
		auto pWeapon = H::Entities.GetWeapon();

		if (pWeapon && rcx == pWeapon->GetClientRenderable())
			return true;
	}

	return CALL_ORIGINAL(rcx);
}