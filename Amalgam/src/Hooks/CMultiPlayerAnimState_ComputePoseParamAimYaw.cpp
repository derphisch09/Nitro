#include "../SDK/SDK.h"

MAKE_SIGNATURE(CMultiPlayerAnimState_ComputePoseParamAimYaw, "client.dll", "40 53 55 56 57 48 83 EC 78 48 8B 01", 0x0);

MAKE_HOOK(CMultiPlayerAnimState_ComputePoseParamAimYaw, S::CMultiPlayerAnimState_ComputePoseParamAimYaw(), void, void* rcx, CStudioHdr* pStudioHdr)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CMultiPlayerAnimState_ComputePoseParamAimYaw[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, pStudioHdr);
#endif

	CALL_ORIGINAL(rcx, pStudioHdr);

	CMultiPlayerAnimState* const m_AnimState = reinterpret_cast<CMultiPlayerAnimState*>(rcx);

	if (!m_AnimState)
		return;

	CBasePlayer* const m_Entity = m_AnimState->m_pEntity;

	if (!m_Entity)
		return;

	QAngle m_Angle = m_Entity->GetAbsAngles();
	m_Angle.y = m_AnimState->m_flCurrentFeetYaw;
	m_Entity->SetAbsAngles(m_Angle);
}