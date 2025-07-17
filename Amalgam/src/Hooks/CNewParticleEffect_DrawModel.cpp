#include "../SDK/SDK.h"

MAKE_SIGNATURE(CNewParticleEffect_DrawModel, "client.dll", "55 8B EC A1 ? ? ? ? 81 EC ? ? ? ? 83 78 30 00 57 8B F9 0F 84 ? ? ? ? A1 ? ? ? ? 83 78 30 00 74 0B 8B 8F ? ? ? ? 89 4D FC EB 09 8B 87", 0x0);

MAKE_HOOK(CNewParticleEffect_DrawModel, S::CNewParticleEffect_DrawModel(), int, void* rcx, int flags)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CNewParticleEffect_DrawModel[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, flags);
#endif

	if (!Vars::Visuals::ParticlesIgnoreZ.Value)
		return CALL_ORIGINAL(rcx, flags);

	if (const auto& pRC = I::MaterialSystem->GetRenderContext())
	{
		pRC->DepthRange(0.0f, 0.02f);
		const int nReturn = CALL_ORIGINAL(rcx, flags);
		pRC->DepthRange(0.0f, 1.0f);
		return nReturn;
	}

	return CALL_ORIGINAL(rcx, flags);
}