#pragma once

#include "Interface.h"

#include "../Misc/Datamap.h"
#include "../Misc/dt_send.h"
#include "../Misc/edict_t.h"
#include "../Misc/ServerClass.h"

class CGlobalVars;
class CSaveRestoreData;
class IServerGCLobby;

typedef int QueryCvarCookie_t;

typedef enum
{
	eQueryCvarValueStatus_ValueIntact = 0,	// It got the value fine.
	eQueryCvarValueStatus_CvarNotFound = 1,
	eQueryCvarValueStatus_NotACvar = 2,		// There's a ConCommand, but it's not a ConVar.
	eQueryCvarValueStatus_CvarProtected = 3	// The cvar was marked with FCVAR_SERVER_CAN_NOT_QUERY, so the server is not allowed to have its value.
} EQueryCvarValueStatus;

class IServerGameDLL
{
public:
	virtual bool DLLInit(CreateInterfaceFn engineFactory, CreateInterfaceFn physicsFactory, CreateInterfaceFn fileSystemFactory, CGlobalVars* pGlobals) = 0;
	virtual bool ReplayInit(CreateInterfaceFn fnReplayFactory) = 0;
	virtual bool GameInit(void) = 0;
	virtual bool LevelInit(char const* pMapName, char const* pMapEntities, char const* pOldLevel, char const* pLandmarkName, bool loadGame, bool background) = 0;
	virtual void ServerActivate(edict_t* pEdictList, int edictCount, int clientMax) = 0;
	virtual void GameFrame(bool simulating) = 0;
	virtual void PreClientUpdate(bool simulating) = 0;
	virtual void LevelShutdown(void) = 0;
	virtual void GameShutdown(void) = 0;
	virtual void DLLShutdown(void) = 0;
	virtual float GetTickInterval(void) const = 0;
	virtual ServerClass* GetAllServerClasses(void) = 0;
	virtual const char* GetGameDescription(void) = 0;
	virtual void CreateNetworkStringTables(void) = 0;
	virtual CSaveRestoreData* SaveInit(int size) = 0;
	virtual void SaveWriteFields(CSaveRestoreData*, const char*, void*, datamap_t*, typedescription_t*, int) = 0;
	virtual void SaveReadFields(CSaveRestoreData*, const char*, void*, datamap_t*, typedescription_t*, int) = 0;
	virtual void SaveGlobalState(CSaveRestoreData*) = 0;
	virtual void RestoreGlobalState(CSaveRestoreData*) = 0;
	virtual void PreSave(CSaveRestoreData*) = 0;
	virtual void Save(CSaveRestoreData*) = 0;
	virtual void GetSaveComment(char* comment, int maxlength, float flMinutes, float flSeconds, bool bNoTime = false) = 0;
	virtual void WriteSaveHeaders(CSaveRestoreData*) = 0;
	virtual void ReadRestoreHeaders(CSaveRestoreData*) = 0;
	virtual void Restore(CSaveRestoreData*, bool) = 0;
	virtual bool IsRestoring() = 0;
	virtual int CreateEntityTransitionList(CSaveRestoreData*, int) = 0;
	virtual void BuildAdjacentMapList(void) = 0;
	virtual bool GetUserMessageInfo(int msg_type, char* name, int maxnamelength, int& size) = 0;
	virtual CStandardSendProxies* GetStandardSendProxies() = 0;
	virtual void PostInit() = 0;
	virtual void Think(bool finalTick) = 0;
	virtual void PreSaveGameLoaded(char const* pSaveName, bool bCurrentlyInGame) = 0;
	virtual bool ShouldHideServer(void) = 0;
	virtual void InvalidateMdlCache() = 0;
	virtual void OnQueryCvarValueFinished(QueryCvarCookie_t iCookie, edict_t* pPlayerEntity, EQueryCvarValueStatus eStatus, const char* pCvarName, const char* pCvarValue) = 0;
	virtual void GameServerSteamAPIActivated(void) = 0;
	virtual void GameServerSteamAPIShutdown(void) = 0;
	virtual void SetServerHibernation(bool bHibernating) = 0;
	virtual IServerGCLobby* GetServerGCLobby() = 0;
	virtual const char* GetServerBrowserMapOverride() = 0;
	virtual const char* GetServerBrowserGameData() = 0;
	virtual void Status(void (*print) (const char* fmt, ...)) = 0;
	virtual void PrepareLevelResources( /* in/out */ char* pszMapName, size_t nMapNameSize, /* in/out */ char* pszMapFile, size_t nMapFileSize) = 0;
	
	enum ePrepareLevelResourcesResult
	{
		ePrepareLevelResources_Prepared,
		ePrepareLevelResources_InProgress
	};

	virtual ePrepareLevelResourcesResult AsyncPrepareLevelResources( /* in/out */ char* pszMapName, size_t nMapNameSize, /* in/out */ char* pszMapFile, size_t nMapFileSize, float* flProgress = NULL) = 0;
	
	enum eCanProvideLevelResult {
		eCanProvideLevel_CannotProvide,
		eCanProvideLevel_CanProvide,
		eCanProvideLevel_Possibly
	};

	virtual eCanProvideLevelResult CanProvideLevel( /* in/out */ char* pMapName, int nMapNameMax) = 0;
	virtual bool IsManualMapChangeOkay(const char** pszReason) = 0;
};

MAKE_INTERFACE_VERSION(IServerGameDLL, ServerGameDLL, "server.dll", "ServerGameDLL012");