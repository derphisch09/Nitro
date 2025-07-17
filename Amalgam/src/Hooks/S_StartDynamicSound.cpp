#include "../SDK/SDK.h"

#include "../Features/Misc/Misc.h"

MAKE_SIGNATURE(S_StartDynamicSound, "engine.dll", "4C 8B DC 57 48 81 EC", 0x0);

MAKE_HOOK(S_StartDynamicSound, S::S_StartDynamicSound(), int, StartSoundParams_t& params)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::S_StartDynamicSound[DEFAULT_BIND])
		return CALL_ORIGINAL(params);
#endif

	H::Entities.ManualNetwork(params);

	if (params.pSfx && F::Misc.ShouldBlockSound(params.pSfx->getname()))
		return 0;

	return CALL_ORIGINAL(params);
}