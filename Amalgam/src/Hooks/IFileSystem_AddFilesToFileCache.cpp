#include "../SDK/SDK.h"

MAKE_HOOK(IFileSystem_AddFilesToFileCache, U::Memory.GetVirtual(I::FileSystem, 103), void, void* rcx, FileCacheHandle_t cacheId, const char** ppFileNames, int nFileNames, const char* pPathID)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::IFileSystem_AddFilesToFileCache[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, cacheId, ppFileNames, nFileNames, pPathID);
#endif

	SDK::Output("IFileSystem_AddFilesToFileCache", std::format("AddFilesToFileCache: {}", nFileNames).c_str());

	for (int i = 0; i < nFileNames; ++i)
		SDK::Output("IFileSystem_AddFilesToFileCache", ppFileNames[i]);
}