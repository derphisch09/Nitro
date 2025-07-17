#include "../SDK/SDK.h"

MAKE_SIGNATURE(CPrediction_IsFirstTimePredicted, "client.dll", "84 C0 74 06 FF 87 98 0E 00 00", 0x0);

MAKE_HOOK(CPrediction_IsFirstTimePredicted, U::Memory.GetVirtual(I::Prediction, 15), bool, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CPrediction_IsFirstTimePredicted[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	static auto m_IsFirstTimePredicted = S::CPrediction_IsFirstTimePredicted();
	const auto m_ReturnAddress = std::uintptr_t(_ReturnAddress());

	if (m_ReturnAddress == m_IsFirstTimePredicted)
		return true;

	return CALL_ORIGINAL(rcx);
}