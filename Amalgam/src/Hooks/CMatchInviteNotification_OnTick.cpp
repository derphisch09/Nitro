#include "../SDK/SDK.h"

MAKE_SIGNATURE(CMatchInviteNotification_OnTick, "client.dll", "40 53 48 83 EC ? 48 8B D9 E8 ? ? ? ? F7 83", 0x0);
MAKE_SIGNATURE(CMatchInviteNotification_AcceptMatch, "client.dll", "40 56 48 83 EC ? 8B 81 ? ? ? ? 48 8B F1 85 C0 74", 0x0);
MAKE_SIGNATURE(CMatchInviteNotification_Flags, "client.dll", "66 0F 2F 83 ? ? ? ? 76 ? 48 8B CB", 0x4);

MAKE_HOOK(CMatchInviteNotification_OnTick, S::CMatchInviteNotification_OnTick(), void, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CMatchInviteNotification_OnTick[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	if (Vars::Misc::Queueing::FreezeQueue.Value)
		*reinterpret_cast<double*>(uintptr_t(rcx) + 616) = 0.0;

	/*if (Vars::Misc::Queueing::AutoAccept.Value)
	{
		if (Vars::Misc::Queueing::AutoAcceptMode.Value == 0 && I::EngineClient->IsInGame())
			return;

		S::CMatchInviteNotification_AcceptMatch();
	}

	if (Vars::Misc::Queueing::AutoJoinCooldown.Value)
	{
		const auto m_Notification = std::uintptr_t(rcx);
		static auto m_Offset = std::int32_t(S::CMatchInviteNotification_Flags());
		const auto m_Flags = std::uint32_t(m_Notification + m_Offset);

		if ((m_Flags & ~2))
			return;
	}*/

	CALL_ORIGINAL(rcx);
}