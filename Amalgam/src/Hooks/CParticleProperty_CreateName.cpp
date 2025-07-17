#include "../SDK/SDK.h"

MAKE_SIGNATURE(CParticleProperty_CreateName, "client.dll", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 48 8B 59 ? 49 8B F1", 0x0);
MAKE_SIGNATURE(CWeaponMedigun_UpdateEffects_CreateName_Call1, "client.dll", "E8 ? ? ? ? 49 8B CC F3 0F 11 74 24", 0x5);
MAKE_SIGNATURE(CWeaponMedigun_UpdateEffects_CreateName_Call2, "client.dll", "E8 ? ? ? ? 41 8B 14 24 48 8B D8", 0x5);
MAKE_SIGNATURE(CWeaponMedigun_ManageChargeEffect_CreateName_Call, "client.dll", "E8 ? ? ? ? 48 89 86 ? ? ? ? 48 89 BE", 0x5);

MAKE_HOOK(CParticleProperty_CreateName, S::CParticleProperty_CreateName(), void*, void* rcx, const char* pszParticleName, ParticleAttachment_t iAttachType, const char* pszAttachmentName)
{
#ifdef DEBUG_HOOKS
    if (!Vars::Hooks::CParticleProperty_CreateName[DEFAULT_BIND])
        return CALL_ORIGINAL(rcx, pszParticleName, iAttachType, pszAttachmentName);
#endif

    static const auto dwUpdateEffects1 = S::CWeaponMedigun_UpdateEffects_CreateName_Call1();
    static const auto dwUpdateEffects2 = S::CWeaponMedigun_UpdateEffects_CreateName_Call2();
    static const auto dwManageChargeEffect = S::CWeaponMedigun_ManageChargeEffect_CreateName_Call();

    const auto dwRetAddr = uintptr_t(_ReturnAddress());

    bool bUpdateEffects = dwRetAddr == dwUpdateEffects1 || dwRetAddr == dwUpdateEffects2, bManageChargeEffect = dwRetAddr == dwManageChargeEffect;
   
    if (bUpdateEffects || bManageChargeEffect)
    {
        auto pLocal = H::Entities.GetLocal();

        if (!pLocal)
            return CALL_ORIGINAL(rcx, pszParticleName, iAttachType, pszAttachmentName);

        /* // probably not needed
        auto pWeapon = pLocal->GetWeaponFromSlot(SLOT_SECONDARY);
        if (!pWeapon || pWeapon->GetWeaponID() != TF_WEAPON_MEDIGUN)
            return CALL_ORIGINAL(rcx, pszParticleName, iAttachType, pszAttachmentName);
        */

        auto pModel = pLocal->GetRenderedWeaponModel();

        if (!pModel || rcx != &pModel->m_Particles())
            return CALL_ORIGINAL(rcx, pszParticleName, iAttachType, pszAttachmentName);

        bool bBlue = pLocal->m_iTeamNum() == TF_TEAM_BLUE;

        if (bUpdateEffects)
        {
            switch (FNV1A::Hash32(Vars::Visuals::Effects::MedigunBeam.Value.c_str()))
            {
            case FNV1A::Hash32Const("Default"): break;
            case FNV1A::Hash32Const("None"): return nullptr;
            case FNV1A::Hash32Const("Uber"): pszParticleName = bBlue ? "medicgun_beam_blue_invun" : "medicgun_beam_red_invun"; break;
            case FNV1A::Hash32Const("Dispenser"): pszParticleName = bBlue ? "dispenser_heal_blue" : "dispenser_heal_red"; break;
            case FNV1A::Hash32Const("Passtime"): pszParticleName = "passtime_beam"; break;
            case FNV1A::Hash32Const("Bombonomicon"): pszParticleName = "bombonomicon_spell_trail"; break;
            case FNV1A::Hash32Const("White"): pszParticleName = "medicgun_beam_machinery_stage3"; break;
            case FNV1A::Hash32Const("Orange"): pszParticleName = "medicgun_beam_red_trail_stage3"; break;
            default: pszParticleName = Vars::Visuals::Effects::MedigunBeam.Value.c_str();
            }
        }
        else if (bManageChargeEffect)
        {
            switch (FNV1A::Hash32(Vars::Visuals::Effects::MedigunCharge.Value.c_str()))
            {
            case FNV1A::Hash32Const("Default"): break;
            case FNV1A::Hash32Const("None"): return nullptr;
            case FNV1A::Hash32Const("Electrocuted"): pszParticleName = bBlue ? "electrocuted_blue" : "electrocuted_red"; break;
            case FNV1A::Hash32Const("Halloween"): pszParticleName = "ghost_pumpkin"; break;
            case FNV1A::Hash32Const("Fireball"): pszParticleName = bBlue ? "spell_fireball_small_trail_blue" : "spell_fireball_small_trail_red"; break;
            case FNV1A::Hash32Const("Teleport"): pszParticleName = bBlue ? "spell_teleport_blue" : "spell_teleport_red"; break;
            case FNV1A::Hash32Const("Burning"): pszParticleName = "superrare_burning1"; break;
            case FNV1A::Hash32Const("Scorching"): pszParticleName = "superrare_burning2"; break;
            case FNV1A::Hash32Const("Purple energy"): pszParticleName = "superrare_purpleenergy"; break;
            case FNV1A::Hash32Const("Green energy"): pszParticleName = "superrare_greenenergy"; break;
            case FNV1A::Hash32Const("Nebula"): pszParticleName = "unusual_invasion_nebula"; break;
            case FNV1A::Hash32Const("Purple stars"): pszParticleName = "unusual_star_purple_parent"; break;
            case FNV1A::Hash32Const("Green stars"): pszParticleName = "unusual_star_green_parent"; break;
            case FNV1A::Hash32Const("Sunbeams"): pszParticleName = "superrare_beams1"; break;
            case FNV1A::Hash32Const("Spellbound"): pszParticleName = "unusual_spellbook_circle_purple"; break;
            case FNV1A::Hash32Const("Purple sparks"): pszParticleName = "unusual_robot_orbiting_sparks2"; break;
            case FNV1A::Hash32Const("Yellow sparks"): pszParticleName = "unusual_robot_orbiting_sparks"; break;
            case FNV1A::Hash32Const("Green zap"): pszParticleName = "unusual_zap_green"; break;
            case FNV1A::Hash32Const("Yellow zap"): pszParticleName = "unusual_zap_yellow"; break;
            case FNV1A::Hash32Const("Plasma"): pszParticleName = "superrare_plasma1"; break;
            case FNV1A::Hash32Const("Frostbite"): pszParticleName = "unusual_eotl_frostbite"; break;
            case FNV1A::Hash32Const("Time warp"): pszParticleName = bBlue ? "unusual_robot_time_warp2" : "unusual_robot_time_warp"; break;
            case FNV1A::Hash32Const("Purple souls"): pszParticleName = "unusual_souls_purple_parent"; break;
            case FNV1A::Hash32Const("Green souls"): pszParticleName = "unusual_souls_green_parent"; break;
            case FNV1A::Hash32Const("Bubbles"): pszParticleName = "unusual_bubbles"; break;
            case FNV1A::Hash32Const("Hearts"): pszParticleName = "unusual_hearts_bubbling"; break;
            default: pszParticleName = Vars::Visuals::Effects::MedigunCharge.Value.c_str();
            }
        }
    }

	return CALL_ORIGINAL(rcx, pszParticleName, iAttachType, pszAttachmentName);
}