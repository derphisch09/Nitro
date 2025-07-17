#pragma once
#include "../Main/CCollisionProperty.h"
#include "../Main/IAchievementMgr.h"
#include "../Main/INetChannelInfo.h"
#include "../Main/IServerNetworkable.h"
#include "../Misc/bitbuf.h"
#include "../Misc/ChecksumCRC.h"
#include "../Misc/edict_t.h"
#include "../Misc/ServerClass.h"
#include "../Misc/VPlane.h"
#include "../Steam/SteamClientPublic.h"
#include "../Definitions.h"
#include "../Main/KeyValues.h"

#define PRINTF_FORMAT_STRING

class IRecipientFilter;
struct client_textmessage_t;
class IScratchPad3D;
class CCheckTransmitInfo;
class CSharedEdictChangeInfo;
class IChangeInfoAccessor;
class CGamestatsData;
struct bbox_t;
class IServer;
typedef int QueryCvarCookie_t;

typedef struct player_info_s
{
	char name[MAX_PLAYER_NAME_LENGTH];
	int userID;
	char guid[SIGNED_GUID_LEN + 1];
	uint32 friendsID;
	char friendsName[MAX_PLAYER_NAME_LENGTH];
	bool fakeplayer;
	bool ishltv;
	bool isreplay;
	CRC32_t customFiles[MAX_CUSTOM_FILES];
	unsigned char filesDownloaded;
} PlayerInfo_t;

class IVEngineServer
{
public:
	virtual void		ChangeLevel(const char* s1, const char* s2) = 0;
	virtual int			IsMapValid(const char* filename) = 0;
	virtual bool		IsDedicatedServer(void) = 0;
	virtual int			IsInEditMode(void) = 0;
	virtual int			PrecacheModel(const char* s, bool preload = false) = 0;
	virtual int			PrecacheSentenceFile(const char* s, bool preload = false) = 0;
	virtual int			PrecacheDecal(const char* name, bool preload = false) = 0;
	virtual int			PrecacheGeneric(const char* s, bool preload = false) = 0;
	virtual bool		IsModelPrecached(char const* s) const = 0;
	virtual bool		IsDecalPrecached(char const* s) const = 0;
	virtual bool		IsGenericPrecached(char const* s) const = 0;
	virtual int			GetClusterForOrigin(const Vec3& org) = 0;
	virtual int			GetPVSForCluster(int cluster, int outputpvslength, unsigned char* outputpvs) = 0;
	virtual bool		CheckOriginInPVS(const Vec3& org, const unsigned char* checkpvs, int checkpvssize) = 0;
	virtual bool		CheckBoxInPVS(const Vec3& mins, const Vec3& maxs, const unsigned char* checkpvs, int checkpvssize) = 0;
	virtual int			GetPlayerUserId(const edict_t* e) = 0;
	virtual const char* GetPlayerNetworkIDString(const edict_t* e) = 0;
	virtual int			GetEntityCount(void) = 0;
	virtual int			IndexOfEdict(const edict_t* pEdict) = 0;
	virtual edict_t* PEntityOfEntIndex(int iEntIndex) = 0;
	virtual INetChannelInfo* GetPlayerNetInfo(int playerIndex) = 0;
	virtual edict_t* CreateEdict(int iForceEdictIndex = -1) = 0;
	virtual void		RemoveEdict(edict_t* e) = 0;
	virtual void* PvAllocEntPrivateData(long cb) = 0;
	virtual void		FreeEntPrivateData(void* pEntity) = 0;
	virtual void* SaveAllocMemory(size_t num, size_t size) = 0;
	virtual void		SaveFreeMemory(void* pSaveMem) = 0;
	virtual void		EmitAmbientSound(int entindex, const Vec3& pos, const char* samp, float vol, soundlevel_t soundlevel, int fFlags, int pitch, float delay = 0.0f) = 0;
	virtual void        FadeClientVolume(const edict_t* pEdict, float fadePercent, float fadeOutSeconds, float holdTime, float fadeInSeconds) = 0;
	virtual int			SentenceGroupPick(int groupIndex, char* name, int nameBufLen) = 0;
	virtual int			SentenceGroupPickSequential(int groupIndex, char* name, int nameBufLen, int sentenceIndex, int reset) = 0;
	virtual int			SentenceIndexFromName(const char* pSentenceName) = 0;
	virtual const char* SentenceNameFromIndex(int sentenceIndex) = 0;
	virtual int			SentenceGroupIndexFromName(const char* pGroupName) = 0;
	virtual const char* SentenceGroupNameFromIndex(int groupIndex) = 0;
	virtual float		SentenceLength(int sentenceIndex) = 0;
	virtual void		ServerCommand(const char* str) = 0;
	virtual void		ServerExecute(void) = 0;
	virtual void		ClientCommand(edict_t* pEdict, PRINTF_FORMAT_STRING const char* szFmt, ...) = 0;
	virtual void		LightStyle(int style, const char* val) = 0;
	virtual void		StaticDecal(const Vec3& originInEntitySpace, int decalIndex, int entityIndex, int modelIndex, bool lowpriority) = 0;
	virtual void		Message_DetermineMulticastRecipients(bool usepas, const Vec3& origin, CBitVec< ABSOLUTE_PLAYER_LIMIT >& playerbits) = 0;
	virtual bf_write* EntityMessageBegin(int ent_index, ServerClass* ent_class, bool reliable) = 0;
	virtual bf_write* UserMessageBegin(IRecipientFilter* filter, int msg_type) = 0;
	virtual void		MessageEnd(void) = 0;
	virtual void		ClientPrintf(edict_t* pEdict, const char* szMsg) = 0;
	virtual void		Con_NPrintf(int pos, PRINTF_FORMAT_STRING const char* fmt, ...) = 0;
	virtual void		Con_NXPrintf(const struct con_nprint_s* info, PRINTF_FORMAT_STRING const char* fmt, ...) = 0;
	virtual void		SetView(const edict_t* pClient, const edict_t* pViewent) = 0;
	virtual float		Time(void) = 0;
	virtual void		CrosshairAngle(const edict_t* pClient, float pitch, float yaw) = 0;
	virtual void        GetGameDir(char* szGetGameDir, int maxlength) = 0;
	virtual int 		CompareFileTime(const char* filename1, const char* filename2, int* iCompare) = 0;
	virtual bool		LockNetworkStringTables(bool lock) = 0;
	virtual edict_t* CreateFakeClient(const char* netname) = 0;
	virtual const char* GetClientConVarValue(int clientIndex, const char* name) = 0;
	virtual const char* ParseFile(const char* data, char* token, int maxlen) = 0;
	virtual bool		CopyFile(const char* source, const char* destination) = 0;
	virtual void		ResetPVS(byte* pvs, int pvssize) = 0;
	virtual void		AddOriginToPVS(const Vec3& origin) = 0;
	virtual void		SetAreaPortalState(int portalNumber, int isOpen) = 0;
	virtual void		PlaybackTempEntity(IRecipientFilter& filter, float delay, const void* pSender, const SendTable* pST, int classID) = 0;
	virtual int			CheckHeadnodeVisible(int nodenum, const byte* pvs, int vissize) = 0;
	virtual int			CheckAreasConnected(int area1, int area2) = 0;
	virtual int			GetArea(const Vec3& origin) = 0;
	virtual void		GetAreaBits(int area, unsigned char* bits, int buflen) = 0;
	virtual bool		GetAreaPortalPlane(Vec3 const& vViewOrigin, int portalKey, VPlane* pPlane) = 0;
	virtual bool		LoadGameState(char const* pMapName, bool createPlayers) = 0;
	virtual void		LoadAdjacentEnts(const char* pOldLevel, const char* pLandmarkName) = 0;
	virtual void		ClearSaveDir() = 0;
	virtual const char* GetMapEntitiesString() = 0;
	virtual client_textmessage_t* TextMessageGet(const char* pName) = 0;
	virtual void		LogPrint(const char* msg) = 0;
	virtual void		BuildEntityClusterList(edict_t* pEdict, PVSInfo_t* pPVSInfo) = 0;
	virtual void SolidMoved(edict_t* pSolidEnt, ICollideable* pSolidCollide, const Vec3* pPrevAbsOrigin, bool testSurroundingBoundsOnly) = 0;
	virtual void TriggerMoved(edict_t* pTriggerEnt, bool testSurroundingBoundsOnly) = 0;
	virtual ISpatialPartition* CreateSpatialPartition(const Vec3& worldmin, const Vec3& worldmax) = 0;
	virtual void 		DestroySpatialPartition(ISpatialPartition*) = 0;
	virtual void		DrawMapToScratchPad(IScratchPad3D* pPad, unsigned long iFlags) = 0;
	virtual const CBitVec<MAX_EDICTS>* GetEntityTransmitBitsForClient(int iClientIndex) = 0;
	virtual bool		IsPaused() = 0;
	virtual void		ForceExactFile(const char* s) = 0;
	virtual void		ForceModelBounds(const char* s, const Vec3& mins, const Vec3& maxs) = 0;
	virtual void		ClearSaveDirAfterClientLoad() = 0;
	virtual void		SetFakeClientConVarValue(edict_t* pEntity, const char* cvar, const char* value) = 0;
	virtual void		ForceSimpleMaterial(const char* s) = 0;
	virtual int			IsInCommentaryMode(void) = 0;
	virtual void		SetAreaPortalStates(const int* portalNumbers, const int* isOpen, int nPortals) = 0;
	virtual void		NotifyEdictFlagsChange(int iEdict) = 0;
	virtual const CCheckTransmitInfo* GetPrevCheckTransmitInfo(edict_t* pPlayerEdict) = 0;
	virtual CSharedEdictChangeInfo* GetSharedEdictChangeInfo() = 0;
	virtual void			AllowImmediateEdictReuse() = 0;
	virtual bool		IsInternalBuild(void) = 0;
	virtual IChangeInfoAccessor* GetChangeAccessor(const edict_t* pEdict) = 0;
	virtual char const* GetMostRecentlyLoadedFileName() = 0;
	virtual char const* GetSaveFileName() = 0;
	virtual void MultiplayerEndGame() = 0;
	virtual void ChangeTeam(const char* pTeamName) = 0;
	virtual void CleanUpEntityClusterList(PVSInfo_t* pPVSInfo) = 0;
	virtual void SetAchievementMgr(IAchievementMgr* pAchievementMgr) = 0;
	virtual IAchievementMgr* GetAchievementMgr() = 0;
	virtual int	GetAppID() = 0;
	virtual bool IsLowViolence() = 0;
	virtual QueryCvarCookie_t StartQueryCvarValue(edict_t* pPlayerEntity, const char* pName) = 0;
	virtual void InsertServerCommand(const char* str) = 0;
	virtual bool GetPlayerInfo(int ent_num, PlayerInfo_t* pinfo) = 0;
	virtual bool IsClientFullyAuthenticated(edict_t* pEdict) = 0;
	virtual void SetDedicatedServerBenchmarkMode(bool bBenchmarkMode) = 0;
	virtual void SetGamestatsData(CGamestatsData* pGamestatsData) = 0;
	virtual CGamestatsData* GetGamestatsData() = 0;
	virtual const CSteamID* GetClientSteamID(edict_t* pPlayerEdict) = 0;
	virtual const CSteamID* GetGameServerSteamID() = 0;
	virtual void ClientCommandKeyValues(edict_t* pEdict, KeyValues* pCommand) = 0;
	virtual const CSteamID* GetClientSteamIDByPlayerIndex(int entnum) = 0;
	virtual int GetClusterCount() = 0;
	virtual int GetAllClusterBounds(bbox_t* pBBoxList, int maxBBox) = 0;
	virtual edict_t* CreateFakeClientEx(const char* netname, bool bReportFakeClient = true) = 0;
	virtual int GetServerVersion() const = 0;
	virtual float GetServerTime() const = 0;
	virtual IServer* GetIServer() = 0;
	virtual bool IsPlayerNameLocked(const edict_t* pEdict) = 0;
	virtual bool CanPlayerChangeName(const edict_t* pEdict) = 0;
	enum eFindMapResult {
		eFindMap_Found,
		eFindMap_NotFound,
		eFindMap_FuzzyMatch,
		eFindMap_NonCanonical,
		eFindMap_PossiblyAvailable
	};
	virtual eFindMapResult FindMap( /* in/out */ char* pMapName, int nMapNameMax) = 0;
	virtual void SetPausedForced(bool bPaused, float flDuration = -1.f) = 0;
};

MAKE_INTERFACE_VERSION(IVEngineServer, EngineServer, "engine.dll", "VEngineServer023");