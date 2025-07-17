#include "../SDK/SDK.h"

#include "../Features/Spectate/Spectate.h"
#include "../Features/Visuals/Killstreak/Killstreak.h"

MAKE_HOOK(CViewRender_LevelShutdown, U::Memory.GetVirtual(I::ViewRender, 2), void, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CViewRender_LevelShutdown[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	F::Spectate.m_iIntendedTarget = -1;
	F::Killstreak.Reset();
	CALL_ORIGINAL(rcx);
}