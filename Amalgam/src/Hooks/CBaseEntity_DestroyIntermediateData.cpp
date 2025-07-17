#include "../SDK/SDK.h"

MAKE_SIGNATURE(CBaseEntity_DestroyIntermediateData, "client.dll", "40 56 48 83 EC 20 48 83 B9 ? ? ? ? ? 48 8B F1 74 5A", 0x0);

MAKE_HOOK(CBaseEntity_DestroyIntermediateData, S::CBaseEntity_DestroyIntermediateData(), void, CBaseEntity* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CBaseEntity_DestroyIntermediateData[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	//F::Datamap->RestoreOldDataDesc(rcx->GetPredDescMap());
	return CALL_ORIGINAL(rcx);
}