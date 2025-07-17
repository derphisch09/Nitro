#include "../SDK/SDK.h"

MAKE_SIGNATURE(MIX_PaintChannels, "engine.dll", "55 8B EC 81 EC ? ? ? ? 8B 0D ? ? ? ? 53 33 DB 89 5D D0 89 5D D4 8B 01 89 5D D8 89 5D DC 85 C0 74 3C 68 ? ? ? ? 68 ? ? ? ? 68 ? ? ? ? 68", 0x0);

MAKE_HOOK(MIX_PaintChannels, S::MIX_PaintChannels(), void, void* rcx, int endtime, bool bIsUnderwater)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::MIX_PaintChannels[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, endtime, bIsUnderwater);
#endif

	CALL_ORIGINAL(rcx, endtime, bIsUnderwater);
}