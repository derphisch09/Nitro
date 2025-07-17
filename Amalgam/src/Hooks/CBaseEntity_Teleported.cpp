#include "../SDK/SDK.h"

MAKE_SIGNATURE(CBaseEntity_Teleported, "client.dll", "40 53 55 56 57 48 83 EC 78 48 8B 01", 0x0);
MAKE_SIGNATURE(CBaseAnimating_SetupBones_CBaseEntity_Teleported, "client.dll", "84 C0 75 18 41 0F B6 86 AC 00 00 00", 0x0);

MAKE_HOOK(CBaseEntity_Teleported, S::CBaseEntity_Teleported(), bool, CBaseEntity* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CBaseEntity_Teleported[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	static auto m_TeleportedCall = S::CBaseAnimating_SetupBones_CBaseEntity_Teleported();
	const auto m_ReturnAddress = std::uintptr_t(_ReturnAddress());

	if (m_ReturnAddress == m_TeleportedCall)
		return true;

	return CALL_ORIGINAL(rcx);
}