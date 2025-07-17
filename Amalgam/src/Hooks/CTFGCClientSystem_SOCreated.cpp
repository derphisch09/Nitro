#include "../SDK/SDK.h"

class CTFLobbyInvite
{
public:
	BYTE pad_0000[32];
	uint64 uLobbyID; // 0x0020
};

MAKE_SIGNATURE(CTFGCClientSystem_SOCreated, "client.dll", "49 8B D0 48 81 C1 ? ? ? ? 45 33 C0", 0x0);

MAKE_HOOK(CTFGCClientSystem_SOCreated, S::CTFGCClientSystem_SOCreated(), void, void* rcx, void* not_used, void** pObject)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CTFGCClientSystem_SOCreated[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, not_used, pObject);
#endif

	if (pObject)
	{
		auto uType = reinterpret_cast<unsigned int(*)(void*)>(U::Memory.GetVirtual(pObject, 1))(pObject);
		SDK::Output("CTFGCClientSystem_SOCreated", std::format("SO created: {}", uType).c_str(), Color_t(255, 255, 255, 255), true, true);

		if (Vars::Misc::Queueing::AutoCasualJoin.Value)
		{
			if (uType == 2008)
			{
				uint64 uLobbyID = reinterpret_cast<CTFLobbyInvite*>(pObject)->uLobbyID;
				SDK::Output("CTFGCClientSystem_SOCreated", std::format("Joining {}..", uLobbyID).c_str(), Color_t(255, 255, 255, 255), true, true);
				I::TFGCClientSystem->RequestAcceptMatchInvite(uLobbyID);
			}
			else if (uType == 2004)
			{
				CALL_ORIGINAL(rcx, not_used, pObject);
				return I::TFGCClientSystem->JoinMMMatch();
			}
		}
	}

	return CALL_ORIGINAL(rcx, not_used, pObject);
}