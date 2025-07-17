#include "../SDK/SDK.h"

MAKE_HOOK(IMaterialSystem_CreateNamedRenderTargetTextureEx2, U::Memory.GetVirtual(I::MaterialSystem, 87), ITexture*, void* rcx, const char* pRTName, int w, int h, RenderTargetSizeMode_t sizeMode, ImageFormat format, MaterialRenderTargetDepth_t depth, unsigned int textureFlags, unsigned int renderTargetFlags)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::IMaterialSystem_CreateNamedRenderTargetTextureEx2[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, pRTName, w, h, sizeMode, format, depth, textureFlags, renderTargetFlags);
#endif

	return CALL_ORIGINAL(rcx, pRTName, 0, 0, sizeMode, format, depth, textureFlags, renderTargetFlags);
}