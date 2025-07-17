#include "../SDK/SDK.h"

#include "../Features/Animations/Animations.h"

MAKE_SIGNATURE(CTFPlayer_OnNewModel, "client.dll", "48 89 5C 24 10 56 48 83 EC 20 48 8B D9 E8 ?? ?? ?? ?? 48 8B CB", 0x0);

MAKE_HOOK(CTFPlayer_OnNewModel, S::CTFPlayer_OnNewModel(), CStudioHdr*, CTFPlayer* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CTFPlayer_OnNewModel[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	if (rcx->m_bPredictable())
	{
		if (F::Animations.m_FakeAnimState)
		{
			F::Animations.m_FakeAnimState->ClearAnimationState();
			F::Animations.m_FakeAnimState->m_PoseParameterData = {};
			F::Animations.m_FakeAnimState->m_bPoseParameterInit = false;
		}
	}

	return CALL_ORIGINAL(rcx);
}