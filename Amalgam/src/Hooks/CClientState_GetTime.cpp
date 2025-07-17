#include "../SDK/SDK.h"

MAKE_SIGNATURE(CClientState_GetTime, "engine.dll", "E8 ? ? ? ? 8B 43 30", 0x0);
MAKE_SIGNATURE(CL_FireEvents_CClientState_GetTime, "engine.dll", "E8 ? ? ? ? 0F 2F 45 04 0F 82 ? ? ? ?", 0x5);

MAKE_HOOK(CClientState_GetTime, S::CClientState_GetTime(), float, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CClientState_GetTime[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	static auto m_GetTimeCall = S::CL_FireEvents_CClientState_GetTime();
	const auto m_ReturnAddress = std::uintptr_t(_ReturnAddress());

	if (m_ReturnAddress == m_GetTimeCall)
		return std::numeric_limits<float>::max();

	return CALL_ORIGINAL(rcx);
}