#include "../SDK/SDK.h"
#include "../Features/EnginePrediction/EnginePrediction.h"

MAKE_HOOK(CPrediction_InPrediction, U::Memory.GetVirtual(I::Prediction, 14), bool, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CPrediction_FinishMove[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	F::EnginePrediction.m_bInPrediction = true;
	return CALL_ORIGINAL(rcx);
}