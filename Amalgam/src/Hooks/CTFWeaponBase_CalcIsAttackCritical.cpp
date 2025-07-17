#include "../SDK/SDK.h"

#include "../Features/CritHack/CritHack.h"

MAKE_HOOK(CTFWeaponBase_CalcIsAttackCritical, S::CTFWeaponBase_CalcIsAttackCritical(), void, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CTFWeaponBase_CalcIsAttackCritical[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

<<<<<<< Updated upstream
	auto pWeapon = reinterpret_cast<CTFWeaponBase*>(rcx);

	const auto nPreviousWeaponMode = pWeapon->m_iWeaponMode();
	pWeapon->m_iWeaponMode() = TF_WEAPON_PRIMARY_MODE;
	if (I::Prediction->m_bFirstTimePredicted)
	{
		*G::RandomSeed() = F::CritHack.m_iWishRandomSeed;
		CALL_ORIGINAL(rcx);
=======
	auto pWeapon = H::Entities.GetWeapon();

	if (!pWeapon)
		return CALL_ORIGINAL(rcx);

	CTFPlayer* const player = pWeapon->m_hOwner().Get()->As<CTFPlayer>();

	if (!player)
		return CALL_ORIGINAL(rcx);

	CUserCmd* const cmd = player->m_pCurrentCommand();

	if (!cmd)
		return CALL_ORIGINAL(rcx);

	if (F::CritHack.CalcIsAttackCriticalHandler(player, pWeapon))
	{
		const int iOldTickcount = I::GlobalVars->tickcount;
		const int iOldFramecount = I::GlobalVars->framecount;

		I::GlobalVars->framecount = cmd->command_number;

		const auto nPreviousWeaponMode = pWeapon->m_iWeaponMode();

		pWeapon->m_iWeaponMode() = TF_WEAPON_PRIMARY_MODE;
		CALL_ORIGINAL(rcx);
		pWeapon->m_iWeaponMode() = nPreviousWeaponMode;

		I::GlobalVars->framecount = iOldFramecount;
		I::GlobalVars->tickcount = iOldTickcount;
>>>>>>> Stashed changes
	}
	else // fixes minigun and flamethrower buggy crit sounds for the most part
	{
		float flOldCritTokenBucket = pWeapon->m_flCritTokenBucket();
		int nOldCritChecks = pWeapon->m_nCritChecks();
		int nOldCritSeedRequests = pWeapon->m_nCritSeedRequests();
		float flOldLastRapidFireCritCheckTime = pWeapon->m_flLastRapidFireCritCheckTime();
		float flOldCritTime = pWeapon->m_flCritTime();
		CALL_ORIGINAL(rcx);
		pWeapon->m_flCritTokenBucket() = flOldCritTokenBucket;
		pWeapon->m_nCritChecks() = nOldCritChecks;
		pWeapon->m_nCritSeedRequests() = nOldCritSeedRequests;
		pWeapon->m_flLastRapidFireCritCheckTime() = flOldLastRapidFireCritCheckTime;
		pWeapon->m_flCritTime() = flOldCritTime;
	}
	pWeapon->m_iWeaponMode() = nPreviousWeaponMode;
}