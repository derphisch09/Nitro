#include "../SDK/SDK.h"
#include "../Features/Visuals/Killstreak/Killstreak.h"

MAKE_HOOK(CGameEventManager_FireEventClientSide, U::Memory.GetVirtual(I::GameEventManager, 8), bool, IGameEventManager2* rcx, IGameEvent* pEvent)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CGameEventManager_FireEventClientSide[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, pEvent);
#endif

	auto uHash = FNV1A::Hash32(pEvent->GetName());

	if (uHash == FNV1A::Hash32Const("player_death"))
	{
		if (Vars::Visuals::Other::KillstreakWeapons.Value)
		{
			F::Killstreak.PlayerDeath(pEvent);
		}

		//F::Misc.PlayerDeath(pEvent);
	}

	if (uHash == FNV1A::Hash32Const("player_spawn"))
	{
		if (Vars::Visuals::Other::KillstreakWeapons.Value)
		{
			F::Killstreak.PlayerSpawn(pEvent);
		}
	}

	//if (uHash == FNV1A::Hash32Const("player_hurt"))
	//{
	//	F::AutoHeal.ProcessPlayerHurt(pEvent);
	//}

	//if (uHash == FNV1A::Hash32Const("party_chat"))
	//{
	//	const auto msg = pEvent->GetString("text");

	//	if (SDK::StartsWith(msg, "TODO@"))
	//	{
	//		if (Vars::Misc::PartyNetworking.Value)
	//		{
	//			F::Networking.HandleMessage(msg);
	//		}

	//		return false;
	//	}
	//}

	//if (uHash == FNV1A::Hash32Const("vote_cast"))
	//{
	//	VoteCast(pEvent);
	//}

	return CALL_ORIGINAL(rcx, pEvent);
}