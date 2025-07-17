#include "../SDK/SDK.h"

MAKE_SIGNATURE(CBaseEntity_PreEntityPacketReceived, "client.dll", "40 53 48 83 EC 20 48 8B 01 48 8B D9 85 D2", 0x0);

MAKE_HOOK(CBaseEntity_PreEntityPacketReceived, S::CBaseEntity_PreEntityPacketReceived(), void, CBaseEntity* rcx, int commands_acknowledged)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CBaseEntity_PreEntityPacketReceived[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, commands_acknowledged);
#endif

	auto pLocal = H::Entities.GetLocal();

	if (!pLocal)
		return CALL_ORIGINAL(rcx, commands_acknowledged);

	CBasePlayer* const player = rcx->As<CBasePlayer>();
	//F::CompressionHandler->PreEntityPacketReceived(player, commands_acknowledged);
	return CALL_ORIGINAL(rcx, commands_acknowledged);
}