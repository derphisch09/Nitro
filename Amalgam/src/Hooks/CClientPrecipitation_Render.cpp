#include "../SDK/SDK.h"

MAKE_SIGNATURE(CClientPrecipitation_Render, "client.dll", "55 8B EC 81 EC ? ? ? ? 33 C0 89 45 FC 39 05 ? ? ? ? 0F 8E ? ? ? ? 53 56 57 8D 49 00 8B 3D ? ? ? ? 8B 3C 87 A1", 0x0);

MAKE_HOOK(CClientPrecipitation_Render, S::CClientPrecipitation_Render(), void, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CClientPrecipitation_Render[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	return CALL_ORIGINAL(rcx);
}