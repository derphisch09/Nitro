#include "../SDK/SDK.h"

MAKE_SIGNATURE(CBasePlayer_ProcessUsercmds, "server.dll", "40 53 55 56 57 41 54 48 83 EC ? 4C 89 6C 24", 0x0);
MAKE_SIGNATURE(CTFWeaponBase_IncrementAmmo, "server.dll", "40 53 57 48 83 EC ? 48 8B D9 E8 ? ? ? ? 48 8B C8", 0x0);

MAKE_HOOK(CBasePlayer_ProcessUsercmds, S::CBasePlayer_ProcessUsercmds(), void, void* rcx, CUserCmd* cmds, int numcmds, int totalcmds, int dropped_packets, bool paused)
{
	bool bInAttack = false;

	for (int i = totalcmds - 1; i >= 0; i--)
	{
		CUserCmd* pCmd = &cmds[totalcmds - 1 - i];

		if (pCmd && pCmd->buttons & IN_ATTACK)
			bInAttack = true;
	}

	if (bInAttack)
	{
		//SDK::Output("ProcessUsercmds", std::format("{}: {}", SDK::PlatFloatTime(), std::bit_cast<int32_t>(float(SDK::PlatFloatTime() * 1000.0)) & 255).c_str(), { 255, 0, 0, 255 });

		//auto pPlayer = reinterpret_cast<CTFPlayer*>(rcx);

		//float flTime = TICKS_TO_TIME(pPlayer->m_nTickBase());
		//float flAttack = pPlayer->m_flNextAttack();
		//SDK::Output("ProcessUsercmds", std::format("{}, {}, {}", flTime - flAttack, TIME_TO_TICKS(flAttack - flTime), flTime < flAttack).c_str());
		//SDK::OutputClient("ProcessUsercmds", std::format("{}, {}, {}", flTime - flAttack, TIME_TO_TICKS(flAttack - flTime), flTime < flAttack).c_str(), pPlayer);
	}

	if (G::ServerHitboxes)
	{
		G::DebugTarget = reinterpret_cast<CTFPlayer*>(rcx);

		if (!(I::GlobalVars->tickcount % G::ServerHitboxesRate))
		{
			for (CBaseEntity* pEntity = I::GlobalEntityList->FirstEnt(); pEntity; pEntity = I::GlobalEntityList->NextEnt(pEntity))
			{
				auto pPlayer = pEntity->As<CTFPlayer>();

				if (!pEntity->IsPlayer() || pEntity->entindex() == G::DebugTarget->entindex())
					continue;

				pPlayer->DrawServerHitboxes(TICK_INTERVAL * G::ServerHitboxesRate, true);
			}
		}
	}

	return CALL_ORIGINAL(rcx, cmds, numcmds, totalcmds, dropped_packets, paused);
}

MAKE_HOOK(CTFWeaponBase_IncrementAmmo, S::CTFWeaponBase_IncrementAmmo(), void, void* rcx)
{
	auto pWeapon = reinterpret_cast<CTFWeaponBase*>(rcx);
	auto pLocal = pWeapon->m_hOwnerEntity().Get()->As<CTFPlayer>();

	if (pLocal && pWeapon)
	{
		SDK::Output("IncrementAmmo", std::format("{}\n\t{}, {}\n\t{}, {}",
			pWeapon->m_iClip1(),
			TIME_TO_TICKS(pLocal->m_flNextAttack() - I::GlobalVars->curtime),
			pLocal->m_flNextAttack() - I::GlobalVars->curtime,
			TIME_TO_TICKS(I::GlobalVars->curtime - pWeapon->m_flReloadPriorNextFire()),
			I::GlobalVars->curtime - pWeapon->m_flReloadPriorNextFire()).c_str());
	}

	CALL_ORIGINAL(rcx);
}