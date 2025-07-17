#pragma once

#include "../../Utils/Feature/Feature.h"

#include "Interfaces/CClientModeShared.h"
#include "Interfaces/CClientState.h"
#include "Interfaces/CGlobalVarsBase.h"
#include "Interfaces/CServerTools.h"
#include "Interfaces/CTFGameRules.h"
#include "Interfaces/CTFGCClientSystem.h"
#include "Interfaces/CTFInventoryManager.h"
#include "Interfaces/CTFPartyClient.h"
#include "Interfaces/IBaseClientDLL.h"
#include "Interfaces/IClientEntityList.h"
#include "Interfaces/ICVar.h"
#include "Interfaces/IDemoPlayer.h"
#include "Interfaces/IDemoRecorder.h"
#include "Interfaces/IEngineTrace.h"
#include "Interfaces/IEngineVGui.h"
#include "Interfaces/IFileSystem.h"
#include "Interfaces/IGameEvents.h"
#include "Interfaces/IGameMovement.h"
#include "Interfaces/IInput.h"
#include "Interfaces/IInputSystem.h"
#include "Interfaces/IKeyValuesSystem.h"
#include "Interfaces/IMaterialSystem.h"
#include "Interfaces/IMatSystemSurface.h"
#include "Interfaces/IMemAlloc.h"
#include "Interfaces/IMoveHelper.h"
#include "Interfaces/IPanel.h"
#include "Interfaces/IPredictableList.h"
#include "Interfaces/IPredictionSystem.h"
#include "Interfaces/IStudioRender.h"
#include "Interfaces/IUniformRandomStream.h"
#include "Interfaces/IVEngineClient.h"
#include "Interfaces/IViewRender.h"
#include "Interfaces/IVModelInfo.h"
#include "Interfaces/IVModelRender.h"
#include "Interfaces/IVRenderView.h"
#include "Interfaces/Prediction.h"
#include "Interfaces/SteamInterfaces.h"
#include "Interfaces/ViewRenderBeams.h"
#include "Interfaces/VPhysics.h"

#include "Misc/IMDLCache.h"

#include <d3d9.h>
MAKE_INTERFACE_SIGNATURE_SEARCH(IDirect3DDevice9, DirectXDevice, "shaderapi", "48 8B 0D ? ? ? ? 48 8B 01 FF 50 ? 8B F8", 0x0, 1)

class CNullInterfaces
{
private:
	bool m_bFailed = false;

public:
	bool Initialize();
};

ADD_FEATURE_CUSTOM(CNullInterfaces, Interfaces, H);

/*
class IFileSystem
{
public:
	bool LoadKeyValues(KeyValues &head, KeyValuesPreloadType_t type, char const *filename, char const *pPathID = 0)
	{
		return mem::callVirtual<76, bool, KeyValues &, KeyValuesPreloadType_t, char const *, char const *>(this, head, type, filename, pPathID);
	}
};
MAKE_IFACE(IFileSystem, file_system, mem::findBytes("client.dll", "48 8B 0D ? ? ? ? 4C 8D 05 ? ? ? ? 48 83 C1 ? 48 8D 94 24 ? ? ? ? 45 33 C9").fixRip(3).deref());

class IPredictableList
{
public:
	C_BaseEntity *GetPredictable(int slot)
	{
		return mem::callVirtual<0, C_BaseEntity *>(this, slot);
	}

	int GetPredictableCount()
	{
		return mem::callVirtual<1, int>(this);
	}
};
MAKE_IFACE(IPredictableList, predictables, mem::findBytes("client.dll", "48 8B 0D ? ? ? ? 48 8B 01 FF 50 08 33 DB 8B F0 85 C0 7E 37 0F 1F 40 00").fixRip(3).deref());

class IDemoPlayer
{
public:
	bool IsPlayingBack()
	{
		return mem::callVirtual<6, bool>(this);
	}
};
MAKE_IFACE(IDemoPlayer, demo_player, mem::findBytes("engine.dll", "48 8B 0D ? ? ? ? 40 B7").fixRip(3).deref());

class IDemoRecorder
{
public:
	bool IsRecording()
	{
		return mem::callVirtual<4, bool>(this);
	}

	bool RecordUserInput(int command_number)
	{
		return mem::callVirtual<9, bool>(this, command_number);
	}
};
MAKE_IFACE(IDemoRecorder, demo_recorder, mem::findBytes("engine.dll", "48 8B 0D ? ? ? ? 8D 56").fixRip(3).deref());

class IPhysicsCollision
{
public:
	CPhysCollide *BBoxToCollide(const Vector &mins, const Vector &maxs)
	{
		return mem::callVirtual<29, CPhysCollide *, const Vector &, const Vector &>(this, mins, maxs);
	}
};
MAKE_IFACE(IPhysicsCollision, physics_col, mem::findInterface("vphysics.dll", "VPhysicsCollision007"));

class CSteamAPIContext
{
public:
	ISteamFriends *SteamFriends()
	{
		return *reinterpret_cast<ISteamFriends **>(reinterpret_cast<uintptr_t>(this) + 16);
	}
};
MAKE_IFACE(CSteamAPIContext, steam_api_context, mem::findBytes("client.dll", "48 8B 05 ? ? ? ? 48 8B 48 30 48 85 C9 74 06").fixRip(3).deref());
*/