#include "../SDK/SDK.h"

MAKE_SIGNATURE(CNetChannel_ProcessPacket, "engine.dll", "44 88 44 24 18 48 89 54 24 10 53", 0x0);

MAKE_HOOK(CNetChannel_ProcessPacket, S::CNetChannel_ProcessPacket(), void, CNetChannel* rcx, uint8_t* packet, bool header)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CNetChannel_ProcessPacket[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, packet, header);
#endif

	CALL_ORIGINAL(rcx, packet, header);
	I::EngineClient->FireEvents();
}