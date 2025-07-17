#include "../SDK/SDK.h"

MAKE_HOOK(IFileSystem_AsyncReadMultiple, U::Memory.GetVirtual(I::FileSystem, 37), FSAsyncStatus_t, void* rcx, const FileAsyncRequest_t* pRequests, int nRequests, FSAsyncControl_t* phControls)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::IFileSystem_AsyncReadMultiple[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, pRequests, nRequests, phControls);
#endif

	for (int i = 0; pRequests && i < nRequests; ++i)
	{
		if (SDK::BlacklistFile(pRequests[i].pszFilename))
		{
			if (nRequests > 1)
				SDK::Output("IFileSystem_AsyncReadMultiple", std::format("FIXME: blocked AsyncReadMultiple for {} requests due to some filename being blacklisted", nRequests).c_str());
			
			return FSASYNC_ERR_FILEOPEN;
		}
	}

	return CALL_ORIGINAL(rcx, pRequests, nRequests, phControls);
}