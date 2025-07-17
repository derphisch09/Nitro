#include "../SDK/SDK.h"
#include "../Features/Misc/Misc.h"

MAKE_HOOK(IBaseClientDLL_PostEntity, U::Memory.GetVirtual(I::BaseClientDLL, 6), void, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::IBaseClientDLL_PostEntity[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	CALL_ORIGINAL(rcx);

	I::EngineClient->ClientCmd_Unrestricted("r_maxdlights 69420");
	I::EngineClient->ClientCmd_Unrestricted("r_dynamic 1");
}