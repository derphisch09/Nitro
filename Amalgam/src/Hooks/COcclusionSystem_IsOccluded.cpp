#include "../SDK/SDK.h"

MAKE_SIGNATURE(COcclusionSystem_IsOccluded, "client.dll", "55 8B EC A1 ? ? ? ? 81 EC ? ? ? ? 83 78 30 00 57 8B F9 0F 84 ? ? ? ? A1 ? ? ? ? 83 78 30 00 74 0B 8B 8F ? ? ? ? 89 4D FC EB 09 8B 87", 0x0);

MAKE_HOOK(COcclusionSystem_IsOccluded, S::COcclusionSystem_IsOccluded(), bool, void* rcx, const Vec3& vecAbsMins, const Vec3& vecAbsMaxs)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::COcclusionSystem_IsOccluded[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, vecAbsMins, vecAbsMaxs);
#endif

	if (!I::OcclusionSystem)
		I::OcclusionSystem = static_cast<IOcclusionSystem*>(rcx);

	return CALL_ORIGINAL(rcx, vecAbsMins, vecAbsMaxs);
}