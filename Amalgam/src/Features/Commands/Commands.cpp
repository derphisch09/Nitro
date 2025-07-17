#include "Commands.h"

#include "../../Core/Core.h"
#include "../ImGui/Menu/Menu.h"
#include "../Configs/Configs.h"
#include "../Players/PlayerUtils.h"
#include "../Misc/Misc.h"

#include <utility>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/join.hpp>

bool CCommands::Run(const std::string& sCmd, std::deque<std::string>& vArgs)
{
	auto uHash = FNV1A::Hash32(sCmd.c_str());
	if (!m_mCommands.contains(uHash))
		return false;

	m_mCommands[uHash](vArgs);
	return true;
}

void CCommands::Register(const std::string& sName, CommandCallback fCallback)
{
	m_mCommands[FNV1A::Hash32(sName.c_str())] = std::move(fCallback);
}

void CCommands::Initialize()
{
	Register("queue", [](const std::deque<std::string>& vArgs)
		{
			if (!I::TFPartyClient)
				return;

			if (I::TFPartyClient->BInQueueForMatchGroup(k_eTFMatchGroup_Casual_Default))
				return;

			if (I::EngineClient->IsDrawingLoadingImage())
				return;

			static bool bHasLoaded = false;
			if (!bHasLoaded)
			{
				I::TFPartyClient->LoadSavedCasualCriteria();
				bHasLoaded = true;
			}
			I::TFPartyClient->RequestQueueForMatch(k_eTFMatchGroup_Casual_Default);
		});

	Register("load", [](const std::deque<std::string>& args)
		{
			if (args.empty())
			{
				SDK::Output("Usage:\n\tload <config_name>");
				return;
			}

			F::Configs.LoadConfig(args[0], true);
		});

	Register("setcvar", [](const std::deque<std::string>& vArgs)
		{
			if (vArgs.size() < 2)
			{
				SDK::Output("Usage:\n\tsetcvar <cvar> <value>");
				return;
			}

			std::string sCVar = vArgs[0];
			auto pCVar = I::CVar->FindVar(sCVar.c_str());
			if (!pCVar)
			{
				SDK::Output(std::format("Could not find {}", sCVar).c_str());
				return;
			}

			auto vArgs2 = vArgs; vArgs2.pop_front();
			std::string sValue = boost::algorithm::join(vArgs2, " ");
			boost::replace_all(sValue, "\"", "");
			pCVar->SetValue(sValue.c_str());
			SDK::Output(std::format("Set {} to {}", sCVar, sValue).c_str());
		});

	Register("getcvar", [](const std::deque<std::string>& vArgs)
		{
			if (vArgs.size() != 1)
			{
				SDK::Output("Usage:\n\tgetcvar <cvar>");
				return;
			}

			std::string sCVar = vArgs[0];
			auto pCVar = I::CVar->FindVar(sCVar.c_str());
			if (!pCVar)
			{
				SDK::Output(std::format("Could not find {}", sCVar).c_str());
				return;
			}

			SDK::Output(std::format("Value of {} is {}", sCVar, pCVar->GetString()).c_str());
		});

	Register("clearchat", [](const std::deque<std::string>& vArgs)
		{
			I::ClientModeShared->m_pChatElement->SetText("");
		});

	Register("menu", [](const std::deque<std::string>& vArgs)
		{
			I::MatSystemSurface->SetCursorAlwaysVisible(F::Menu.m_bIsOpen = !F::Menu.m_bIsOpen);
		});

	Register("unload", [](const std::deque<std::string>& vArgs)
		{
			if (F::Menu.m_bIsOpen)
				I::MatSystemSurface->SetCursorAlwaysVisible(F::Menu.m_bIsOpen = false);
			U::Core.m_bUnload = true;
		});

	Register("ignore", [](const std::deque<std::string>& vArgs)
		{
			if (vArgs.size() < 2)
			{
				SDK::Output("Usage:\n\tignore <id32> <tag>");
				return;
			}

			uint32_t uFriendsID = 0;
			try
			{
				uFriendsID = std::stoul(vArgs[0]);
			}
			catch (...)
			{
				SDK::Output("Invalid ID32 format");
				return;
			}

			if (!uFriendsID)
			{
				SDK::Output("Invalid ID32");
				return;
			}

			const std::string& sTag = vArgs[1];
			int iTagID = F::PlayerUtils.GetTag(sTag);
			if (iTagID == -1)
			{
				SDK::Output(std::format("Invalid tag: {}", sTag).c_str());
				return;
			}

			auto pTag = F::PlayerUtils.GetTag(iTagID);
			if (!pTag || !pTag->m_bAssignable)
			{
				SDK::Output(std::format("Tag {} is not assignable", sTag).c_str());
				return;
			}

			if (F::PlayerUtils.HasTag(uFriendsID, iTagID))
			{
				F::PlayerUtils.RemoveTag(uFriendsID, iTagID, true);
				SDK::Output(std::format("Removed tag {} from ID32 {}", sTag, uFriendsID).c_str());
			}
			else
			{
				F::PlayerUtils.AddTag(uFriendsID, iTagID, true);
				SDK::Output(std::format("Added tag {} to ID32 {}", sTag, uFriendsID).c_str());
			}
		});

	Register("crash", [](const std::deque<std::string>& vArgs) // if you want to time out of a server and rejoin
		{
			switch (vArgs.empty() ? 0 : FNV1A::Hash32(vArgs.front().c_str()))
			{
			case FNV1A::Hash32Const("true"):
			case FNV1A::Hash32Const("t"):
			case FNV1A::Hash32Const("1"):
				break;
			default:
				Vars::Debug::CrashLogging.Value = false; // we are voluntarily crashing, don't give out log if we don't want one
			}
			reinterpret_cast<void(*)()>(0)();
		});

	/*Register("rent_item", [](const std::deque<std::string>& vArgs)
		{
			if (vArgs.size() != 1)
			{
				SDK::Output("Usage:\n\trent_item <item_def_index>");
				return;
			}

			item_definition_index_t iDefIdx;
			try
			{
				iDefIdx = atoi(vArgs[0].c_str());
			}
			catch (const std::invalid_argument&)
			{
				SDK::Output("Invalid item_def_index");
				return;
			}

			F::AutoItem.Rent(iDefIdx);
		});*/

	Register("achievement_unlock", [](const std::deque<std::string>& vArgs)
		{
			F::Misc.UnlockAchievements();
		});

	/*Register("binds", [](const std::deque<std::string>& vArgs)
		{
			// Movement
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind w +forward").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind s +back").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind a +moveleft").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind d +moveright").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind SPACE +jump").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind CTRL +duck").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind ' +moveup").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind / +movedown").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind PGUP +lookup").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind PGDN +lookdown").c_str());

			// Communication
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind v +voicerecord").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind y say").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind u say_team").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind z voice_menu_1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind x voice_menu_2").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind c voice_menu_3").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind e voicemenu 0 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind p say_party").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind PGUP +lookup").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind PGDN +lookdown").c_str());

			// Gameplay
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind , changeteam").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind m open_charinfo_direct").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind n open_charinfo_backpack").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind l dropitem").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind g +taunt").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind h +use_action_slot_item").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind i showmapinfo").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind f +inspect").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind F2 show_quest_log").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind F3 show_matchmaking").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind F4 player_ready_toggle").c_str());

			// Class specific
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind b lastdisguise").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind - disguiseteam").c_str());

			// Combat
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind MOUSE1 +attack").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind MOUSE2 +attack2").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind MOUSE3 +attack3").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind r +reload").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind MWHEELUP invprev").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind MWHEELDOWN invnext").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind q lastinv").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind 1 slot1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind 2 slot2").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind 3 slot3").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind 4 slot4").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind 5 slot5").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind 6 slot6").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind 7 slot7").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind 8 slot8").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind 9 slot9").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind 0 slot10").c_str());

			// Miscellaneous
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind t impulse 201").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind TAB +showscores").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind F5 screenshot").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind F6 save_replay").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind F7 abuse_report_queue").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind F10 quit prompt").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind ` toggleconsole").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind j cl_trigger_first_notification").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("bind k cl_decline_first_notification").c_str());
		});*/

	Register("optimize", [](const std::deque<std::string>& vArgs)
		{
			// Server
			I::EngineClient->ClientCmd_Unrestricted(std::format("developer 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("sv_cheats 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_lc 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_mmx 1").c_str());


			// Audio
			I::EngineClient->ClientCmd_Unrestricted(std::format("dsp_slow_cpu 1").c_str());

			I::EngineClient->ClientCmd_Unrestricted(std::format("snd_pitchquality 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("snd_spatialize_roundrobin 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("snd_mixahead 0.1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("snd_mix_async 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("snd_async_fullyasync 1").c_str());

			// Debug flooding
			I::EngineClient->ClientCmd_Unrestricted(std::format("adsp_debug 0").c_str()); // Disable "adsp" debugging

			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_clearhinthistory 1").c_str()); // Clear hint history
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_debugrumble 0").c_str()); // Turn off rumble debugging spew
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_rumblescale 0").c_str()); // Disable Scale sensitivity of rumble effects 

			I::EngineClient->ClientCmd_Unrestricted(std::format("mat_debugdepthval 0").c_str()); // Disable depth value debugging
			I::EngineClient->ClientCmd_Unrestricted(std::format("mat_debugdepthvalmax 0").c_str()); // Disable depth max value debugging
			I::EngineClient->ClientCmd_Unrestricted(std::format("mat_debug_postprocessing_effects 0").c_str()); // Disable post-processing effects debugging
			I::EngineClient->ClientCmd_Unrestricted(std::format("mat_dump_rts 0").c_str()); // Disable rts dump

			I::EngineClient->ClientCmd_Unrestricted(std::format("sv_logdownloadlist 0").c_str()); // Disable download list logging

			// Facial expressions
			I::EngineClient->ClientCmd_Unrestricted(std::format("ai_expression_optimization 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("anim_3wayblend 1").c_str());

			I::EngineClient->ClientCmd_Unrestricted(std::format("blink_duration 0.2").c_str());

			I::EngineClient->ClientCmd_Unrestricted(std::format("flex_rules 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("flex_smooth 1").c_str());

			I::EngineClient->ClientCmd_Unrestricted(std::format("phonemefilter 0.1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("phonemesnap 7").c_str());

			I::EngineClient->ClientCmd_Unrestricted(std::format("r_flex 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_eyes 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_teeth 0").c_str());

			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_clientsideeye_lookats 1").c_str());

			// Graphics
			I::EngineClient->ClientCmd_Unrestricted(std::format("mat_specular 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("mat_bumpmap 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("mat_phong 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("mat_picmip 4").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_waterforceexpensive 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("mat_reducefillrate 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("mat_antialias 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("mat_aaquality 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_spraydisable 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_particles_disable_weather 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("mat_mipmaptextures 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_detailfade 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_detaildist 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_drawdetailprops 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("mp_decals 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_decals 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_phys_props_enable 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_phys_props_max 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("props_break_max_pieces 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_propsmaxdist 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("g_ragdoll_fadespeed 10000").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("g_ragdoll_lvfadespeed 10000").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("ragdoll_sleepaftertime 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_ragdoll_fade_time 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_ragdoll_forcefade 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_ragdoll_physics_enable 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("mat_queue_mode 2").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("lod_TransitionDist -1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_lod -1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_rootlod 2").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_shadows 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("mat_hdr_level 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_enable_glows_after_respawn 0").c_str());

			// Hitsound
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_dingalingaling 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_dingaling_volume 0.33").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_dingaling_pitchmindmg 133").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_dingaling_pitchmaxdmg 5").c_str());

			// Hud
			I::EngineClient->ClientCmd_Unrestricted(std::format("hud_freezecamhide 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("hud_medichealtargetmarker 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("hud_medicautocallers 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("hud_medicautocallersthreshold 60").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("hud_fastswitch 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("hud_classautokill 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("hud_combattext 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("hud_combattext_batching 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("hud_combattext_batching_window 2").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("hud_combattext_doesnt_block_overhead_text 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("hud_saytext_time 10").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("hud_deathnotice_time 5").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("hud_achievement_glowtime 0").c_str()); // Duration of glow effect around incremented achievements
			I::EngineClient->ClientCmd_Unrestricted(std::format("hud_achievement_count 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("hud_achievement_tracker 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("hud_autoaim_scale_icon 0").c_str()); // Disabled unused hud element for more fps

			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_mm_dashboard_slide_panel_step 10").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_dashboard_slide_time 0.25").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_item_inspect_model_auto_spin 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_item_inspect_model_spin_rate 30").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_quest_map_tuner_wobble_magnitude 0.01").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_halloween_bonus_ducks_cooldown 10").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_healthicon_height_offset 10").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_hud_num_building_alert_beeps 2").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_rd_finale_beep_time 10").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_hud_no_crosshair_on_scope_zoom 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_hud_show_servertimelimit 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_hud_target_id_alpha 100").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_hud_target_id_offset 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_hud_target_id_show_avatars 2").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_scoreboard_ping_as_text 1").c_str());

			I::EngineClient->ClientCmd_Unrestricted(std::format("sv_motd_unload_on_dismissal 1").c_str());

			// Mouse
			I::EngineClient->ClientCmd_Unrestricted(std::format("m_filter 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("m_customaccel 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("m_mouseaccel1 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("m_mouseaccel2 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("m_mousespeed 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("m_rawinput 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("zoom_sensitivity_ratio 0.793471").c_str());

			// Network
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_cmdrate 66").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_updaterate 66").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_interp 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_interp_npcs 0.1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_interp_ratio 2").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_pred_optimize 2").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_lagcompensation 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_predictweapons 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_smooth 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_smoothtime 0.1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_localnetworkbackdoor 0").c_str());

			I::EngineClient->ClientCmd_Unrestricted(std::format("ex_interp 0.01").c_str());

			I::EngineClient->ClientCmd_Unrestricted(std::format("net_queued_packet_thread 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("net_compresspackets 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("net_splitrate 2").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("net_usesocketsforloopback 0").c_str());

			I::EngineClient->ClientCmd_Unrestricted(std::format("rate 97000").c_str());

			I::EngineClient->ClientCmd_Unrestricted(std::format("sv_allowdownload 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("sv_allowupload 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("sv_parallel_sendsnapshot 1").c_str());

			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_party_force_update").c_str());

			// Occluder system
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_occludeemaxarea 1").c_str()); // Be more conservative with our resolution
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_occluderminarea 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_occludermincount 2").c_str()); // Use the largest 2 occluders

			// Optimizations
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_queued_decals 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_threaded_particles 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_threaded_renderables 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("net_queue_trace 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("studio_queue_mode 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_threaded_client_leaf_system 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_threaded_renderables 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_threaded_particles 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_queued_ropes 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_queued_post_processing 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_threaded_client_shadow_manager 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("snd_async_fullyasync 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_new_impact_effects 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("mat_alphacoverage 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("rope_averagelight 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("hud_achievement_glowtime 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_queued_post_processing 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("sys_minidumpspewlines 500").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("studio_queue_mode 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("mat_queue_mode 2").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_entityclips 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_frustumcullworld 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_worldlistcache 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_occludermincount 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_hud_target_id_show_avatars 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_time_loading_item_panels 0.0001").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_backpack_page_button_delay 0.25").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("lzma_persistent_buffer 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("filesystem_buffer_size 262144").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("filesystem_max_stdio_read 256").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("filesystem_native 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("filesystem_unbuffered_io 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("mod_load_anims_async 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("mod_load_mesh_async 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("mod_load_vcollide_async 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("mod_touchalldata 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("mod_forcedata 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("mod_forcetouchdata 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("voice_steal 2").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("in_usekeyboardsampletime 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_particle_sim_spike_threshold_ms 0").c_str());

			// Ragdolls
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_ragdoll_physics_enable 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_ragdoll_fade_time 15").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_ragdoll_forcefade 0").c_str());

			I::EngineClient->ClientCmd_Unrestricted(std::format("g_ragdoll_fadespeed 600").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("g_ragdoll_lvfadespeed 100").c_str());

			I::EngineClient->ClientCmd_Unrestricted(std::format("ragdoll_sleepaftertime 5.0f").c_str());

			// Shadows
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_blobbyshadows 0").c_str());

			I::EngineClient->ClientCmd_Unrestricted(std::format("r_flashlightdepthtexture 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_shadowmaxrendered 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_shadowrendertotexture 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("r_shadows 0").c_str());

			// Tutorials
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_ask_blacklist_opt_out 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_ask_favorite_opt_out 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_showhelp 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("cl_hud_playerclass_playermodel_showed_confirm_dialog 1").c_str());

			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_explanations_backpackpanel 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_explanations_charinfo_armory_panel 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_explanations_charinfopanel 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_explanations_craftingpanel 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_explanations_discardpanel 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_explanations_store 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_training_has_prompted_for_forums 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_training_has_prompted_for_loadout 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_training_has_prompted_for_offline_practice 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_training_has_prompted_for_options 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_training_has_prompted_for_training 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_taunt_always_show_hint 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_coach_request_nevershowagain 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_show_maps_details_explanation_count 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_show_taunt_explanation_in_class_loadout 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_show_preset_explanation_in_class_loadout 0").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_find_a_match_hint_viewed 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_quest_map_intro_viewed 1").c_str());
			I::EngineClient->ClientCmd_Unrestricted(std::format("tf_warpaint_explanation_viewed 1").c_str());

			I::EngineClient->ClientCmd_Unrestricted(std::format("sb_dontshow_maxplayer_warning 1").c_str());
		});
}