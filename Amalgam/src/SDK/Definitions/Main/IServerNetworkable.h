#pragma once

#include "IHandleEntity.h"
#include "../Misc/bitbuf.h"
#include "../Misc/edict_t.h"
#include "../Misc/ServerClass.h"
#include "../Definitions.h"

#define MAX_FAST_ENT_CLUSTERS 4
#ifdef GetClassName
#undef GetClassName
#endif

class CBaseNetworkable;

struct PVSInfo_t
{
	short m_nHeadNode;
	short m_nClusterCount;
	unsigned short* m_pClusters;
	short m_nAreaNum;
	short m_nAreaNum2;
	float m_vCenter[3];
	unsigned short m_pClustersInline[MAX_FAST_ENT_CLUSTERS];
	friend class CVEngineServer;
};

class IServerNetworkable
{
public:
	virtual IHandleEntity* GetEntityHandle() = 0;
	virtual ServerClass* GetServerClass() = 0;
	virtual edict_t* GetEdict() const = 0;
	virtual const char* GetClassName() const = 0;
	virtual void Release() = 0;
	virtual int AreaNum() const = 0;
	virtual CBaseNetworkable* GetBaseNetworkable() = 0;
	virtual CBaseEntity* GetBaseEntity() = 0;
	virtual PVSInfo_t* GetPVSInfo() = 0;
	virtual ~IServerNetworkable() = 0;

	inline ETFClassID GetClassID()
	{
		if (auto pServerClass = GetServerClass())
			return static_cast<ETFClassID>(pServerClass->m_ClassID);

		return static_cast<ETFClassID>(0);
	}
};