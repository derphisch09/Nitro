#include "../SDK/SDK.h"

MAKE_SIGNATURE(COPRenderSprites_RenderSpriteCard, "client.dll", "48 8B C4 48 89 58 ? 57 41 54", 0x0);

MAKE_HOOK(COPRenderSprites_RenderSpriteCard, S::COPRenderSprites_RenderSpriteCard(), void, void* rcx, void* meshBuilder, void* pCtx, SpriteRenderInfo_t& info, int hParticle, ParticleRenderData_t* pSortList, void* pCamera)
{
#ifdef DEBUG_HOOKS
    if (!Vars::Hooks::COPRenderSprites_RenderSpriteCard[DEFAULT_BIND])
        return CALL_ORIGINAL(rcx, meshBuilder, pCtx, info, hParticle, pSortList, pCamera);
#endif

    if (!(Vars::Visuals::World::Modulations.Value & Vars::Visuals::World::ModulationsEnum::Particle) || Vars::Visuals::UI::CleanScreenshots.Value && I::EngineClient->IsTakingScreenshot())
        return CALL_ORIGINAL(rcx, meshBuilder, pCtx, info, hParticle, pSortList, pCamera);

    info.m_pRGB[((hParticle / 4) * info.m_nRGBStride) + 0].m128_f32[hParticle & 0x3] = float(Vars::Colors::ParticleModulation.Value.r) / 255.f; // red
    info.m_pRGB[((hParticle / 4) * info.m_nRGBStride) + 1].m128_f32[hParticle & 0x3] = float(Vars::Colors::ParticleModulation.Value.g) / 255.f; // green
    info.m_pRGB[((hParticle / 4) * info.m_nRGBStride) + 2].m128_f32[hParticle & 0x3] = float(Vars::Colors::ParticleModulation.Value.b) / 255.f; // blue

    if (Vars::Colors::ParticleModulation.Value.a != 255)
        pSortList->m_nAlpha = Vars::Colors::ParticleModulation.Value.a;

    CALL_ORIGINAL(rcx, meshBuilder, pCtx, info, hParticle, pSortList, pCamera);
}