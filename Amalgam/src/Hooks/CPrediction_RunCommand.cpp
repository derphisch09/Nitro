#include "../SDK/SDK.h"

#include "../Features/Ticks/Ticks.h"

//MAKE_SIGNATURE(CPrediction_RunCommand, "client.dll", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 0F 29 74 24 ? 49 8B E9", 0x0);

std::vector<Vec3> vAngles;

MAKE_HOOK(CPrediction_RunCommand, U::Memory.GetVirtual(I::Prediction, 17), void, void* rcx, CTFPlayer* pPlayer, CUserCmd* pCmd, IMoveHelper* moveHelper)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CPrediction_RunCommand[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, pPlayer, pCmd, moveHelper);
#endif

	CALL_ORIGINAL(rcx, pPlayer, pCmd, moveHelper);

	if (I::MoveHelper == nullptr)
		I::MoveHelper = moveHelper;

	/*if (pPlayer != H::Entities.GetLocal() || F::Ticks.m_bRecharge || pCmd->hasbeenpredicted)
		return;

	auto pAnimState = pPlayer->GetAnimState();
	vAngles.push_back(G::ViewAngles);

	if (!pAnimState || G::Choking)
		return;

	for (auto& vAngle : vAngles)
	{
		pAnimState->Update(vAngle.y, vAngle.x);
		pPlayer->FrameAdvance(TICK_INTERVAL);
	}

	vAngles.clear();*/
}