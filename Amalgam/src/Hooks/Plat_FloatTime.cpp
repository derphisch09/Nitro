#include "../SDK/SDK.h"

MAKE_HOOK(Plat_FloatTime, U::Memory.GetModuleExport<uintptr_t>("tier0.dll", "Plat_FloatTime"), double)
{
	return CALL_ORIGINAL() + G::PlatFloatTimeAdd;
}