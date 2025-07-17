#include "../SDK/SDK.h"

#include "../Core/Core.h"

MAKE_SIGNATURE(HostState_Restart, "engine.dll", "C7 05 ? ? ? ? ? ? ? ? C3 CC CC CC CC CC 48 83 EC", 0x0);

MAKE_HOOK(HostState_Restart, S::HostState_Restart(), void)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::HostState_Restart[DEFAULT_BIND])
		return CALL_ORIGINAL();
#endif

	U::Core.m_bUnload = true;
	CALL_ORIGINAL();
}