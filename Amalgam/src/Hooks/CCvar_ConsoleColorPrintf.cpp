#include "../SDK/SDK.h"

MAKE_HOOK(CCvar_ConsoleColorPrintf, U::Memory.GetVirtual(I::CVar, 23), void, void* rcx, const Color_t& clr, const char* pFormat, ...)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CCvar_ConsoleColorPrintf[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, clr, pFormat);
#endif

	va_list marker;

	char buffer[4096];

	va_start(marker, pFormat);
	vsnprintf_s(buffer, sizeof(buffer), pFormat, marker);
	va_end(marker);

	char* msg = buffer;

	if (!*msg)
		return;

	std::string Message = msg;
	return CALL_ORIGINAL(rcx, clr, "%s", Message.c_str());
}