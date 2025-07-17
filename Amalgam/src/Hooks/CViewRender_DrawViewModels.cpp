#include "../SDK/SDK.h"

#include "../Features/Spectate/Spectate.h"

MAKE_SIGNATURE(CViewRender_DrawViewModels, "client.dll", "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 8B FA", 0x0);

MAKE_HOOK(CViewRender_DrawViewModels, S::CViewRender_DrawViewModels(), void, void* rcx, const CViewSetup& viewRender, bool drawViewmodel)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CTFPlayer_ShouldDraw[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, viewRender, drawViewmodel);
#endif

	CALL_ORIGINAL(rcx, viewRender, F::Spectate.m_iTarget != -1 ? false : drawViewmodel);
}