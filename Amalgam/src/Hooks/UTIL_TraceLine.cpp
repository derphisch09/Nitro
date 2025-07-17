#include "../SDK/SDK.h"

MAKE_SIGNATURE(DisplayDamageFeedback, "client.dll", "E8 ? ? ? ? F3 0F 10 45 ? 83 C4 18 0F 2F 05 ? ? ? ? 8B 75 10", 0x5);

MAKE_HOOK(UTIL_TraceLine, S::UTIL_TraceLine(), void, void* rcx, Vector* vecAbsStart, Vector* vecAbsEnd, unsigned int mask, CTraceFilter* pFilter, CGameTrace* ptr)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::UTIL_TraceLine[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, vecAbsStart, vecAbsEnd, mask, pFilter, ptr);
#endif

	static auto dwDisplayDamageFeedback = S::DisplayDamageFeedback();

	if (reinterpret_cast<DWORD>(_ReturnAddress()) == dwDisplayDamageFeedback && pFilter)
	{
		*reinterpret_cast<float*>(reinterpret_cast<DWORD>(pFilter) + 0x2C) = 1.0f;
		return;
	}

	return CALL_ORIGINAL(rcx, vecAbsStart, vecAbsEnd, mask, pFilter, ptr);
}