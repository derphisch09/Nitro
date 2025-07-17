#include "../SDK/SDK.h"

#include "../Features/EnginePrediction/DatamapModifier.h"

MAKE_SIGNATURE(CBaseEntity_InitPredictable, "client.dll", "40 53 48 83 EC 30 48 8B D9 48 8B 0D ?? ?? ?? ?? 48 8B 01 FF 90 ?? ?? ?? ?? 85", 0x0);

MAKE_HOOK(CBaseEntity_InitPredictable, S::CBaseEntity_InitPredictable(), void, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CBaseEntity_InitPredictable[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	auto pLocal = H::Entities.GetLocal();

	if (pLocal->InCond(TF_COND_DISGUISED))
		return;

	I::MDLCache->BeginLock();

	F::DatamapModifier.IterateDatamaps(pLocal->GetPredDescMap());
	F::DatamapModifier.m_bDatamapInitialize = true;

	I::MDLCache->EndLock();

	return CALL_ORIGINAL(rcx);
}