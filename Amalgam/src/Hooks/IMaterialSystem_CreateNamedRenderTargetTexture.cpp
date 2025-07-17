#include "../SDK/SDK.h"

MAKE_HOOK(IMaterialSystem_CreateNamedRenderTargetTexture, U::Memory.GetVirtual(I::MaterialSystem, 86), ITexture*, void* rcx, const char* pRTName, int w, int h, RenderTargetSizeMode_t sizeMode, ImageFormat format, MaterialRenderTargetDepth_t depth, bool bClampTexCoords, bool bAutoMipMap)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::IMaterialSystem_CreateNamedRenderTargetTexture[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, pRTName, w, h, sizeMode, format, depth, bClampTexCoords, bAutoMipMap);
#endif

	return CALL_ORIGINAL(rcx, pRTName, 0, 0, sizeMode, format, depth, bClampTexCoords, bAutoMipMap);
}