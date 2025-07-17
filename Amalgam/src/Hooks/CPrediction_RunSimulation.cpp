#include "../SDK/SDK.h"

#include "../Features/Animations/Animations.h"
#include "../Features/EnginePrediction/EnginePrediction.h"
#include "../Features/Ticks/Ticks.h"

MAKE_SIGNATURE(CPrediction_RunSimulation, "client.dll", "48 83 EC 38 4C 8B 44", 0x0);

MAKE_HOOK(CPrediction_RunSimulation, S::CPrediction_RunSimulation(), void, void* rcx, int current_command, float curtime, CUserCmd* cmd, CTFPlayer* localPlayer)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CPrediction_RunSimulation[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, current_command, curtime, cmd, localPlayer);
#endif

	static int nStaticDifference = 0;
	const int nLastDifference = nStaticDifference;
	const int nCurrDifference = nStaticDifference = I::ClientState->lastoutgoingcommand - current_command;

#ifndef TICKBASE_DEBUG
	if (F::Ticks.m_bShifted && !nLastDifference && nCurrDifference)
		localPlayer->m_nTickBase() -= F::Ticks.m_iShiftStart - F::Ticks.m_iShiftedGoal - 1;
#else
	static int nStaticCurrentCommand = 0;
	const int nLastCurrentCommand = nStaticCurrentCommand;
	const int nCurrCurrentCommand = nStaticCurrentCommand = current_command;

	static int nStaticTickBase = 0;
	const int nLastTickBase = nStaticTickBase;
	const int nCurrTickBase = nStaticTickBase = localPlayer->m_nTickBase();

	if (F::Ticks.m_bShifted && !nLastDifference && nCurrDifference)
	{
		localPlayer->m_nTickBase() -= F::Ticks.m_iShiftStart - F::Ticks.m_iShiftedGoal - 1;
		nStaticTickBase = localPlayer->m_nTickBase();
	}

	if (Vars::Debug::Info.Value)
	{
		SDK::Output("Packet", std::format("{}, {}, {}", F::Ticks.m_iShiftedTicks, F::Ticks.m_iShiftedGoal, I::ClientState->chokedcommands).c_str(), { 255, 0, 0, 255 });
		
		if (nCurrTickBase != localPlayer->m_nTickBase())
			SDK::Output("Time", std::format("{} -> {} ({})", nCurrTickBase, localPlayer->m_nTickBase(), nCurrTickBase - nLastTickBase).c_str(), { 255, 0, 0, 255 });
		else
			SDK::Output("Time", std::format("{} ({})", localPlayer->m_nTickBase(), nCurrTickBase - nLastTickBase).c_str(), { 255, 0, 0, 255 });
		
		if (nLastCurrentCommand != current_command)
			SDK::Output("Command", std::format("{} -> {} ({})", nLastCurrentCommand, current_command, nCurrCurrentCommand - nLastCurrentCommand).c_str(), { 255, 0, 0, 255 });
		else
			SDK::Output("Command", std::format("{} ({})", current_command, nCurrCurrentCommand - nLastCurrentCommand).c_str(), { 255, 0, 0, 255 });
		
		SDK::Output("Misc", std::format("{}, {}; {}, {}\n", I::ClientState->lastoutgoingcommand, I::ClientState->last_command_ack, I::GlobalVars->frametime, I::ClientState->lastoutgoingcommand - current_command).c_str(), { 255, 0, 0, 255 });
	}
#endif

	F::EnginePrediction.ScalePlayers(localPlayer);
	CALL_ORIGINAL(rcx, current_command, curtime, cmd, localPlayer);

	F::Animations.RunSimulation(localPlayer, cmd, curtime);

	/*if (current_command == F::EnginePrediction.GetLatestCommandNumber() - 1 && F::Animations.m_AllowLocalBoneSetup)
	{
		F::Animations.m_BoneOrigin = localPlayer->m_vecOrigin();
		//lrm->AllowBoneSetup(true);

		localPlayer->InvalidateBoneCache();
		localPlayer->m_fEffects() |= 8;
		localPlayer->SetupBones(F::Animations.m_LocalBones.data(), 128, BONE_USED_BY_ANYTHING, I::GlobalVars->curtime);
		localPlayer->m_fEffects() &= ~8;

		//lrm->AllowBoneSetup(false);
		F::Animations.m_AllowLocalBoneSetup = false;
	}*/

	F::EnginePrediction.RestorePlayers();
}