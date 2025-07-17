#include "../SDK/SDK.h"

MAKE_HOOK(IMaterialSystem_CreateRenderTargetTexture, U::Memory.GetVirtual(I::MaterialSystem, 84), ITexture*, void* rcx, int w, int h, RenderTargetSizeMode_t sizeMode, ImageFormat	format, MaterialRenderTargetDepth_t depth)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::IMaterialSystem_CreateRenderTargetTexture[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, w, h, sizeMode, format, depth);
#endif

	return CALL_ORIGINAL(rcx, 0, 0, sizeMode, format, depth);
}