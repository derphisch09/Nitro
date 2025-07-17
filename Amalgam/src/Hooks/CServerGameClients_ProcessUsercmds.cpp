#include "../SDK/SDK.h"

MAKE_SIGNATURE(CServerGameClients_ProcessUsercmds, "server.dll", "55 8B EC B8 ? ? ? ? E8 ? ? ? ? B9 ? ? ? ? 8D 85 ? ? ? ? EB 06", 0x0);

MAKE_HOOK(CServerGameClients_ProcessUsercmds, S::CServerGameClients_ProcessUsercmds(), float, void* rcx, void* player, bf_read* buf, int numcmds, int totalcmds, int dropped_packets, bool ignore, bool paused)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CServerGameClients_ProcessUsercmds[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, player, buf, numcmds, totalcmds, dropped_packets, ignore, paused);
#endif

	return CALL_ORIGINAL(rcx, player, buf, numcmds, totalcmds, dropped_packets, ignore, paused);
}