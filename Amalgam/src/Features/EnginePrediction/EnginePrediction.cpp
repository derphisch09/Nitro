#include "EnginePrediction.h"

#include "../Ticks/Ticks.h"

void CEnginePrediction::ScalePlayers(CBaseEntity* pLocal)
{
	m_mRestore.clear();

	for (auto pEntity : H::Entities.GetGroup(EGroupType::PLAYERS_ALL))
	{
		auto pPlayer = pEntity->As<CTFPlayer>();
		if (pPlayer == pLocal || pPlayer->IsDormant() || !pPlayer->IsAlive() || pPlayer->IsAGhost())
			continue;

		m_mRestore[pPlayer] = { pPlayer->m_vecMins(), pPlayer->m_vecMaxs() };

		pPlayer->m_vecMins() += 0.125f;
		pPlayer->m_vecMaxs() -= 0.125f;
	}
}

void CEnginePrediction::RestorePlayers()
{
	for (auto& [pPlayer, tRestore] : m_mRestore)
	{
		pPlayer->m_vecMins() = tRestore.m_vecMins;
		pPlayer->m_vecMaxs() = tRestore.m_vecMaxs;
	}
}

int CEnginePrediction::GetLatestCommandNumber()
{
	return I::ClientState->lastoutgoingcommand + I::ClientState->chokedcommands + 1;
}

void CEnginePrediction::Update()
{
	if (I::ClientState->m_nDeltaTick <= 0)
		return;

	I::Prediction->Update(I::ClientState->m_nDeltaTick, true, I::ClientState->last_command_ack, GetLatestCommandNumber() - 1);
}

int CEnginePrediction::GetTickbase(CTFPlayer* pLocal, CUserCmd* pCmd)
{
	static int s_nTick = 0;
	static CUserCmd* s_pLastCmd = nullptr;

	if (pCmd)
	{
		if (!s_pLastCmd || s_pLastCmd->hasbeenpredicted)
			s_nTick = pLocal->m_nTickBase();
		else
			s_nTick++;

		s_pLastCmd = pCmd;
	}

	return s_nTick;
}

float CEnginePrediction::GetServerTime()
{
	return (I::GlobalVars->interval_per_tick * GetTickBase());
}

void CEnginePrediction::Simulate(CTFPlayer* pLocal, CUserCmd* pCmd)
{
	if (!I::MoveHelper)
		return;

	const int nOldFlags = pLocal->m_fFlags();
	const int nOldTickBase = pLocal->m_nTickBase();

	const bool bOldIsFirstPrediction = I::Prediction->m_bFirstTimePredicted;
	const bool bOldInPrediction = I::Prediction->m_bInPrediction;

	//memset(&m_MoveData, 0, sizeof(CMoveData));
	I::MoveHelper->SetHost(pLocal);

	pLocal->m_pCurrentCommand() = pCmd;
	*G::RandomSeed() = MD5_PseudoRandom(pCmd->command_number) & std::numeric_limits<int>::max();

	//pLocal->SetPredictionRandomSeed(pCmd);
	//pLocal->SetPredictionPlayer(pLocal);

	I::Prediction->m_bFirstTimePredicted = false;
	I::Prediction->m_bInPrediction = true;

	I::GameMovement->StartTrackPredictionErrors(pLocal);

	//if (pCmd->weaponselect != NULL)
	//{
	//	CBaseCombatWeapon* pWeapon = dynamic_cast<CBaseCombatWeapon*>(I::ClientEntityList->GetClientEntity(pCmd->weaponselect));
	//
	//	if (pWeapon)
	//		pLocal->SelectItem(pWeapon->GetName(), pCmd->weaponsubtype);
	//}

	pLocal->UpdateButtonState(pCmd->buttons);
	I::Prediction->SetLocalViewAngles(pCmd->viewangles);

	const int iThinkTick = pLocal->m_nNextThinkTick();

	if (pLocal->SetPhysicsRunThink())
	{
		pLocal->PreThink();
	}

	if (iThinkTick > 0 && iThinkTick <= I::GlobalVars->tickcount)
	{
		pLocal->SetNextThink(-1, NULL);
		pLocal->Think();
	}

	Vec2 vOriginalMove; int iOriginalButtons;

	if (m_bDoubletap = m_bInPrediction && (F::Ticks.m_bAntiWarp || F::Ticks.GetTicks(H::Entities.GetWeapon()) && Vars::Doubletap::AntiWarp.Value && pLocal->m_hGroundEntity()))
	{
		m_vOriginalOrigin = pLocal->m_vecOrigin();
		m_vOriginalVelocity = pLocal->m_vecVelocity();

		vOriginalMove = { pCmd->forwardmove, pCmd->sidemove };
		iOriginalButtons = pCmd->buttons;

		bool bOriginalWarp = F::Ticks.m_bAntiWarp;

		F::Ticks.m_bAntiWarp = true;
		F::Ticks.AntiWarp(pLocal, pCmd);
		F::Ticks.m_bAntiWarp = bOriginalWarp;
	}

	I::Prediction->SetupMove(pLocal, pCmd, I::MoveHelper, &m_MoveData);
	ScalePlayers(pLocal);

	I::GameMovement->ProcessMovement(pLocal, &m_MoveData);
	RestorePlayers();

	I::Prediction->FinishMove(pLocal, pCmd, &m_MoveData);
	I::MoveHelper->ProcessImpacts();

	m_bPostThink = true;
	pLocal->PostThink();
	m_bPostThink = false;

	I::GameMovement->FinishTrackPredictionErrors(pLocal);

	//pLocal->SetPredictionRandomSeed(nullptr);
    //pLocal->SetPredictionPlayer(nullptr);

	if (m_bDoubletap)
	{
		pCmd->forwardmove = vOriginalMove.x, pCmd->sidemove = vOriginalMove.y;
		pCmd->buttons = iOriginalButtons;
	}

	I::MoveHelper->SetHost(nullptr);
	pLocal->m_pCurrentCommand() = nullptr;
	*G::RandomSeed() = -1;

	pLocal->m_fFlags() = nOldFlags;
	pLocal->m_nTickBase() = nOldTickBase;

	I::Prediction->m_bFirstTimePredicted = bOldIsFirstPrediction;
	I::Prediction->m_bInPrediction = bOldInPrediction;

	m_vOrigin = pLocal->m_vecOrigin();
	m_vVelocity = pLocal->m_vecVelocity();
	m_vDirection = { m_MoveData.m_flForwardMove, -m_MoveData.m_flSideMove, m_MoveData.m_flUpMove };
	m_vAngles = m_MoveData.m_vecViewAngles;
}

void CEnginePrediction::Start(CTFPlayer* pLocal, CUserCmd* pCmd)
{
	m_bInPrediction = true;

	if (!pLocal || !pLocal->IsAlive())
		return;

	m_nOldTickCount = I::GlobalVars->tickcount;
	m_flOldCurrentTime = I::GlobalVars->curtime;
	m_flOldFrameTime = I::GlobalVars->frametime;

	//m_iServerTicks = GetTickbase(pLocal, pCmd);

	I::GlobalVars->tickcount = pLocal->m_nTickBase();
	I::GlobalVars->curtime = TICKS_TO_TIME(I::GlobalVars->tickcount);
	I::GlobalVars->frametime = I::Prediction->m_bEnginePaused ? 0.f : TICK_INTERVAL;

	//m_bSimulated = false;

	//if (F::Ticks.GetTicks() && Vars::Doubletap::AntiWarp.Value && pLocal->OnSolid())
	//	return;

	//m_bSimulated = true;

	Simulate(pLocal, pCmd);
}

void CEnginePrediction::End(CTFPlayer* pLocal, CUserCmd* pCmd)
{
	m_bInPrediction = false;

	if (!pLocal || !pLocal->IsAlive())
		return;

	I::GlobalVars->tickcount = m_nOldTickCount;
	I::GlobalVars->curtime = m_flOldCurrentTime;
	I::GlobalVars->frametime = m_flOldFrameTime;

	if (m_bDoubletap && !F::Ticks.m_bAntiWarp && !G::Attacking)
	{
		pLocal->m_vecOrigin() = m_vOriginalOrigin;
		pLocal->m_vecVelocity() = m_vOriginalVelocity;
		pLocal->SetAbsVelocity(m_vOriginalVelocity);

		Simulate(pLocal, pCmd);
	}
}