#include "../SDK/SDK.h"

MAKE_SIGNATURE(CTFTeamStatusPlayerPanel_Update, "client.dll", "40 56 57 48 83 EC ? 48 83 3D", 0x0);

MAKE_HOOK(CTFTeamStatusPlayerPanel_Update, S::CTFTeamStatusPlayerPanel_Update(), bool, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CTFPlayerPanel_GetTeam[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	G::PlayerIndex = *reinterpret_cast<int*>(uintptr_t(rcx) + 580);
	return CALL_ORIGINAL(rcx);
}