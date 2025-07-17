#include "../SDK/SDK.h"

MAKE_HOOK(IBaseClientDLL_PreEntity, U::Memory.GetVirtual(I::BaseClientDLL, 5), void, void* rcx, const char* szMapName)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::IBaseClientDLL_PreEntity[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, szMapName);
#endif

	CALL_ORIGINAL(rcx, szMapName);
}