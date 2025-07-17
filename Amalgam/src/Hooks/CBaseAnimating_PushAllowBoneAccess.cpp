#include "../SDK/SDK.h"

MAKE_SIGNATURE(CBaseAnimating_PushAllowBoneAccess, "client.dll", "55 8B EC 83 EC 20 8D 45 E0 53 56 57 6A 01 68 ? ? ? ? 68 ? ? ? ? 68 ? ? ? ? 68 ? ? ? ? 50 E8 ? ? ? ? 8B 15 ? ? ? ? 83 C4 18 8B 0D", 0x0);

MAKE_HOOK(CBaseAnimating_PushAllowBoneAccess, S::CBaseAnimating_PushAllowBoneAccess(), void, void* rcx, bool bAllowForNormalModels, bool bAllowForViewModels, char const* tagPush)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CBaseAnimating_PushAllowBoneAccess[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, bAllowForNormalModels, bAllowForViewModels, tagPush);
#endif

	return CALL_ORIGINAL(rcx, bAllowForNormalModels, bAllowForViewModels, tagPush);
}