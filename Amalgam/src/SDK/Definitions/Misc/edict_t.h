#pragma once

class IServerNetworkable;
class IServerUnknown;

class CBaseEdict
{
public:
	int	m_fStateFlags;

#if VALVE_LITTLE_ENDIAN
	short m_NetworkSerialNumber;
	short m_EdictIndex;
#else
	short m_EdictIndex;
	short m_NetworkSerialNumber;
#endif

	IServerNetworkable* m_pNetworkable;
	IServerUnknown* m_pUnk;
};

struct edict_t : public CBaseEdict
{
public:
	float freetime;
};