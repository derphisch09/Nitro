#include "../SDK/SDK.h"

#include "../Features/Misc/Misc.h"

MAKE_SIGNATURE(S_StartSound, "engine.dll", "40 53 48 83 EC ? 48 83 79 ? ? 48 8B D9 75 ? 33 C0", 0x0);

MAKE_HOOK(S_StartSound, S::S_StartSound(), int, StartSoundParams_t& params)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::S_StartSound[DEFAULT_BIND])
		return CALL_ORIGINAL(params);
#endif

	if (!params.staticsound)
		H::Entities.ManualNetwork(params);

	if (params.pSfx && F::Misc.ShouldBlockSound(params.pSfx->getname()))
		return 0;

	return CALL_ORIGINAL(params);
}