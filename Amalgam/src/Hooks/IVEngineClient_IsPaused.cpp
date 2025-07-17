#include "../SDK/SDK.h"

MAKE_SIGNATURE(IVEngineClient_IsPaused, "client.dll", "84 C0 75 07 C6 05", 0x0);

MAKE_HOOK(IVEngineClient_IsPaused, U::Memory.GetVirtual(I::EngineClient, 84), bool, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::IVEngineClient_IsPaused[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	static auto m_IsPaused = S::IVEngineClient_IsPaused();
	const auto m_ReturnAddress = std::uintptr_t(_ReturnAddress());

	if (m_ReturnAddress == m_IsPaused)
		return true;

	return CALL_ORIGINAL(rcx);
}