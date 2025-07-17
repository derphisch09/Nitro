#include "../SDK/SDK.h"

MAKE_HOOK(IMaterialSystem_CreateNamedRenderTargetTextureEx, U::Memory.GetVirtual(I::MaterialSystem, 85), ITexture*, void* rcx, const char* pRTName, int w, int h, RenderTargetSizeMode_t sizeMode, ImageFormat format, MaterialRenderTargetDepth_t depth, unsigned int textureFlags, unsigned int renderTargetFlags)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::IMaterialSystem_CreateNamedRenderTargetTextureEx[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, pRTName, w, h, sizeMode, format, depth, textureFlags, renderTargetFlags);
#endif

	return CALL_ORIGINAL(rcx, pRTName, 0, 0, sizeMode, format, depth, textureFlags, renderTargetFlags);
}