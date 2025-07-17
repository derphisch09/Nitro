#include "../SDK/SDK.h"

MAKE_SIGNATURE(CSequenceTransitioner_CheckForSequenceChange, "client.dll", "48 85 D2 0F 84 ? ? ? ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24", 0x0);
//MAKE_SIGNATURE(CSequenceTransitioner_CheckForSequenceChange, "client.dll", "E8 ? ? ? ? 41 8B 86 ? ? ? ? 49 8B CF", 0x0);

MAKE_HOOK(CSequenceTransitioner_CheckForSequenceChange, S::CSequenceTransitioner_CheckForSequenceChange(), void, void* rcx, CStudioHdr* hdr, int nCurSequence, bool bForceNewSequence, bool bInterpolate)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CSequenceTransitioner_CheckForSequenceChange[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, hdr, nCurSequence, bForceNewSequence, bInterpolate);
#endif

	return CALL_ORIGINAL(rcx, hdr, nCurSequence, bForceNewSequence, Vars::Visuals::Removals::Interpolation.Value ? false : bInterpolate);
}