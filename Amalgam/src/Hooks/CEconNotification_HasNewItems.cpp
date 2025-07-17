#include "../SDK/SDK.h"
#include "../../Features/Items/Items.h"

MAKE_HOOK(CEconNotification_HasNewItems, S::CEconNotification_HasNewItems(), CEconNotification*, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CEconNotification_HasNewItems[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	auto* pNotification = CALL_ORIGINAL(rcx);
	F::Items.AddNotifcation(pNotification);
	return pNotification;
}