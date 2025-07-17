#include "../SDK/SDK.h"

MAKE_SIGNATURE(CL_LoadWhitelist, "engine.dll", "55 8B EC 83 EC 0C 83 3D ? ? ? ? ? 0F 8C ? ? ? ? 8B 0D ? ? ? ? 8B 01 8B 40 54 FF D0 D9 5D F8 B9 ? ? ? ? E8 ? ? ? ? D9 5D FC F3 0F 10 45", 0x0);

MAKE_HOOK(CL_LoadWhitelist, S::CL_LoadWhitelist(), void*, void* rcx, void* table, const char* name)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CL_LoadWhitelist[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, table, name);
#endif

	if (Vars::Misc::Exploits::PureBypass.Value)
		return nullptr;

	return CALL_ORIGINAL(rcx, table, name);
}