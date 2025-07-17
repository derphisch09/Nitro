#include "../SDK/SDK.h"

MAKE_SIGNATURE(CNetGraphPanel_DrawTextFields, "client.dll", "55 8B EC A1 ? ? ? ? 81 EC ? ? ? ? 83 78 30 00 57 8B F9 0F 84 ? ? ? ? A1 ? ? ? ? 83 78 30 00 74 0B 8B 8F ? ? ? ? 89 4D FC EB 09 8B 87", 0x0);

MAKE_HOOK(CNetGraphPanel_DrawTextFields, S::CNetGraphPanel_DrawTextFields(), void, void* rcx, int graphvalue, int x, int y, int w, void* graph, void* cmdinfo)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CNetGraphPanel_DrawTextFields[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, graphvalue, x, y, w, graph, cmdinfo);
#endif

	return CALL_ORIGINAL(rcx, graphvalue, x, y, w, graph, cmdinfo);
}