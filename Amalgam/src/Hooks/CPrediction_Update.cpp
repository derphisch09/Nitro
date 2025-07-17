#include "../SDK/SDK.h"

MAKE_HOOK(CPrediction_Update, U::Memory.GetVirtual(I::Prediction, 21), void, void* rcx, bool received_new_world_update, bool validframe, int incoming_acknowledged, int outgoing_command)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CPrediction_Update[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, received_new_world_update, validframe, incoming_acknowledged, outgoing_command);
#endif

	return CALL_ORIGINAL(rcx, true, validframe, incoming_acknowledged, outgoing_command);
}