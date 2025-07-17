#include "../SDK/SDK.h"

MAKE_SIGNATURE(CBaseEntity_PostNetworkDataUpdate, "client.dll", "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 41 54 41 56 48 81 EC 10 01 00 00", 0x0);

MAKE_HOOK(CBaseEntity_PostNetworkDataUpdate, S::CBaseEntity_PostNetworkDataUpdate(), bool, CBaseEntity* rcx, int commands_acknowledged)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CBaseEntity_PostNetworkDataUpdate[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, commands_acknowledged);
#endif

	auto pLocal = H::Entities.GetLocal();

	if (commands_acknowledged <= 0 || pLocal)
		return CALL_ORIGINAL(rcx, commands_acknowledged);

	CBasePlayer* player = rcx->As<CBasePlayer>();

	if (!player || player->deadflag()) 
		return CALL_ORIGINAL(rcx, commands_acknowledged);

	//F::CompressionHandler->PostNetworkDataReceived(player, commands_acknowledged - 1);

	return CALL_ORIGINAL(rcx, commands_acknowledged);
}