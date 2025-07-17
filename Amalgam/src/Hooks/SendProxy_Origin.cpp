#include "../SDK/SDK.h"

MAKE_SIGNATURE(SendProxy_Origin, "server.dll", "48 89 74 24 ? 57 48 83 EC ? 80 3D ? ? ? ? ? 49 8B F1 48 8B FA 74 ? 80 BA ? ? ? ? ? 75 ? BA ? ? ? ? 48 8B CF E8 ? ? ? ? 84 C0 74 ? BA ? ? ? ? 48 89 5C 24 ? 48 8B CF E8 ? ? ? ? 48 8B D0 48 8B CF 48 8B D8 E8 ? ? ? ? 0F B6 13 48 8D 83 ? ? ? ? 48 8B 5C 24 ? EB ? 48 8B 44 24 ? 32 D2 84 D2 48 8D 8F ? ? ? ? 48 0F 45 C8 8B 01 89 06 8B 41 ? 89 46 ? 8B 41", 0x0);
MAKE_SIGNATURE(SendProxy_OriginXY, "server.dll", "48 89 74 24 ? 57 48 83 EC ? 80 3D ? ? ? ? ? 49 8B F1 48 8B FA 74 ? 80 BA ? ? ? ? ? 75 ? BA ? ? ? ? 48 8B CF E8 ? ? ? ? 84 C0 74 ? BA ? ? ? ? 48 89 5C 24 ? 48 8B CF E8 ? ? ? ? 48 8B D0 48 8B CF 48 8B D8 E8 ? ? ? ? 0F B6 13 48 8D 83 ? ? ? ? 48 8B 5C 24 ? EB ? 48 8B 44 24 ? 32 D2 84 D2 48 8D 8F ? ? ? ? 48 0F 45 C8 8B 01 89 06 8B 41 ? 89 46 ? 48 8B 74 24", 0x0);
MAKE_SIGNATURE(SendProxy_OriginZ, "server.dll", "48 89 74 24 ? 57 48 83 EC ? 80 3D ? ? ? ? ? 49 8B F1 48 8B FA 74 ? 80 BA ? ? ? ? ? 75 ? BA ? ? ? ? 48 8B CF E8 ? ? ? ? 84 C0 74 ? BA ? ? ? ? 48 89 5C 24 ? 48 8B CF E8 ? ? ? ? 48 8B D0 48 8B CF 48 8B D8 E8 ? ? ? ? 0F B6 13 48 8D 8B", 0x0);

MAKE_HOOK(SendProxy_Origin, S::SendProxy_Origin(), void, const SendProp* pProp, const void* pStruct, const void* pData, DVariant* pOut)
{
	CALL_ORIGINAL(pProp, pStruct, pData, pOut);

	CBaseEntity* pEntity = (CBaseEntity*)(pStruct);

	if (pEntity && pEntity->IsPlayer())
		SDK::Output("SendProxy_Origin", std::format("{}: {}, {}, {}", pEntity->entindex(), pOut->m_Vector[0], pOut->m_Vector[1], pOut->m_Vector[2]).c_str());
}

MAKE_HOOK(SendProxy_OriginXY, S::SendProxy_OriginXY(), void, const SendProp* pProp, const void* pStruct, const void* pData, DVariant* pOut)
{
	CALL_ORIGINAL(pProp, pStruct, pData, pOut);

	CBaseEntity* pEntity = (CBaseEntity*)(pStruct);

	if (pEntity && pEntity->IsPlayer())
		SDK::Output("SendProxy_OriginXY", std::format("{}: {}, {}", pEntity->entindex(), pOut->m_Vector[0], pOut->m_Vector[1]).c_str());
}

MAKE_HOOK(SendProxy_OriginZ, S::SendProxy_OriginZ(), void, const SendProp* pProp, const void* pStruct, const void* pData, DVariant* pOut)
{
	CALL_ORIGINAL(pProp, pStruct, pData, pOut);

	CBaseEntity* pEntity = (CBaseEntity*)(pStruct);

	if (pEntity && pEntity->IsPlayer())
		SDK::Output("SendProxy_OriginZ", std::format("{}: {}", pEntity->entindex(), pOut->m_Float).c_str());
}