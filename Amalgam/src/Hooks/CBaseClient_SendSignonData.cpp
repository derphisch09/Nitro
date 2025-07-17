#include "../SDK/SDK.h"
#include "../../Features/Chams/DMEChams.h"

MAKE_SIGNATURE(CBaseClient_SendSignonData, "engine.dll", "55 8B EC 83 EC 10 8B 45 08 53 8B D9 C7 45 ? ? ? ? ? 83 78 20 00 0F 8E ? ? ? ? 33 D2 56 89 55 F8 57", 0x0);

MAKE_HOOK(CBaseClient_SendSignonData, S::CBaseClient_SendSignonData(), bool, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CBaseClient_SendSignonData[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	F::DMEChams.CreateMaterials();
	return CALL_ORIGINAL(rcx);
}