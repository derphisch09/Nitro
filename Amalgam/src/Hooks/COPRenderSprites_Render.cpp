#include "../SDK/SDK.h"

MAKE_SIGNATURE(COPRenderSprites_Render, "client.dll", "48 89 54 24 ? 55 53 57 41 55 41 56", 0x0);

MAKE_HOOK(COPRenderSprites_Render, S::COPRenderSprites_Render(), void, void* rcx, IMatRenderContext* pRenderContext, CParticleCollection* pParticles, void* pContext)
{
#ifdef DEBUG_HOOKS
    if (!Vars::Hooks::COPRenderSprites_Render[DEFAULT_BIND])
        return CALL_ORIGINAL(rcx, pRenderContext, pParticles, pContext);
#endif

    if (!Vars::Visuals::Effects::DrawIconsThroughWalls.Value || Vars::Visuals::UI::CleanScreenshots.Value && I::EngineClient->IsTakingScreenshot())
        return CALL_ORIGINAL(rcx, pRenderContext, pParticles, pContext);

    bool bValid = false;

    switch (FNV1A::Hash32(pParticles->m_pDef->m_pszMaterialName))
    {
    // blue icons
    case FNV1A::Hash32Const("effects\\defense_buff_bullet_blue.vmt"):
    case FNV1A::Hash32Const("effects\\defense_buff_explosion_blue.vmt"):
    case FNV1A::Hash32Const("effects\\defense_buff_fire_blue.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_agility_icon_blue.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_haste_icon_blue.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_king_icon_blue.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_knockout_icon_blue.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_plague_icon_blue.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_precision_icon_blue.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_reflect_icon_blue.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_resist_icon_blue.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_strength_icon_blue.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_supernova_icon_blue.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_thorns_icon_blue.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_vampire_icon_blue.vmt"):
    {
        auto pLocal = H::Entities.GetLocal();
        bValid = !pLocal || pLocal->m_iTeamNum() != TF_TEAM_BLUE;
        break;
    }
    // red icons
    case FNV1A::Hash32Const("effects\\defense_buff_bullet_red.vmt"):
    case FNV1A::Hash32Const("effects\\defense_buff_explosion_red.vmt"):
    case FNV1A::Hash32Const("effects\\defense_buff_fire_red.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_agility_icon_red.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_haste_icon_red.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_king_icon_red.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_knockout_icon_red.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_plague_icon_red.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_precision_icon_red.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_reflect_icon_red.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_regen_icon_blue.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_regen_icon_red.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_resist_icon_red.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_strength_icon_red.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_supernova_icon_red.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_thorns_icon_red.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_vampire_icon_red.vmt"):
    {
        auto pLocal = H::Entities.GetLocal();
        bValid = !pLocal || pLocal->m_iTeamNum() != TF_TEAM_RED;
        break;
    }
    // global icons
    /*
    case FNV1A::Hash32Const("effects\\powerup_agility_icon.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_haste_icon.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_king_icon.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_knockout_icon.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_pestilence_icon.vmt"): // is this even used?
    case FNV1A::Hash32Const("effects\\powerup_plague_icon.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_precision_icon.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_reflect_icon.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_regen_icon.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_resist_icon.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_strength_icon.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_supernova_icon.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_thorns_icon.vmt"):
    case FNV1A::Hash32Const("effects\\powerup_vampire_icon.vmt"):
    */
    case FNV1A::Hash32Const("effects\\particle_nemesis_blue.vmt"):
    case FNV1A::Hash32Const("effects\\particle_nemesis_red.vmt"):
    case FNV1A::Hash32Const("effects\\particle_nemesis_burst.vmt"):
    case FNV1A::Hash32Const("effects\\duel_blue.vmt"):
    case FNV1A::Hash32Const("effects\\duel_red.vmt"):
    case FNV1A::Hash32Const("effects\\duel_burst.vmt"):
    case FNV1A::Hash32Const("effects\\crit.vmt"):
    case FNV1A::Hash32Const("effects\\yikes.vmt"):
        bValid = true;
    }
    if (!bValid)
        return CALL_ORIGINAL(rcx, pRenderContext, pParticles, pContext);

    pRenderContext->DepthRange(0.f, 0.2f);
    CALL_ORIGINAL(rcx, pRenderContext, pParticles, pContext);
    pRenderContext->DepthRange(0.f, 1.f);
}