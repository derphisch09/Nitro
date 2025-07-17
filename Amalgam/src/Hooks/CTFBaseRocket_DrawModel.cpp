#include "../SDK/SDK.h"

MAKE_SIGNATURE(CTFBaseRocket_DrawModel, "client.dll", "48 8B 05 ? ? ? ? F3 0F 10 40 ? F3 0F 5C 81 ? ? ? ? 0F 2F 05 ? ? ? ? 73 ? 33 C0 C3 E9 ? ? ? ? CC CC CC CC CC CC CC CC CC CC CC 48 8D 05 ? ? ? ? C3 CC CC CC CC CC CC CC CC 48 89 5C 24", 0x0);

MAKE_HOOK(CTFBaseRocket_DrawModel, S::CTFBaseRocket_DrawModel(), int, CTFBaseRocket* rcx, int flags)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CTFBaseRocket_DrawModel[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, flags);
#endif

	if (rcx)
	{
		float& spawn_time = rcx->m_flSpawnTime();

		if (I::GlobalVars->curtime - spawn_time < 0.2f)
			spawn_time = I::GlobalVars->curtime - 0.2f;
	}

	return CALL_ORIGINAL(rcx, flags);
}