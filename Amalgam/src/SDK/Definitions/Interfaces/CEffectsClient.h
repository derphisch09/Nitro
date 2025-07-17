#pragma once

#include "Interface.h"
#include "../Main/UtlVector.h"
#include "../Types.h"

class CBaseEntity;

class IEffects : public IPredictionSystem
{
public:
	virtual void Beam(const Vector& Start, const Vector& End, int nModelIndex, int nHaloIndex, unsigned char frameStart, unsigned char frameRate, float flLife, unsigned char width, unsigned char endWidth, unsigned char fadeLength, unsigned char noise, unsigned char red, unsigned char green, unsigned char blue, unsigned char brightness, unsigned char speed) = 0;
	virtual void Smoke(const Vector& origin, int modelIndex, float scale, float framerate) = 0;
	virtual void Sparks(const Vector& position, int nMagnitude = 1, int nTrailLength = 1, const Vector* pvecDir = NULL) = 0;
	virtual void Dust(const Vector& pos, const Vector& dir, float size, float speed) = 0;
	virtual void MuzzleFlash(const Vector& vecOrigin, const QAngle& vecAngles, float flScale, int iType) = 0;
	virtual void MetalSparks(const Vector& position, const Vector& direction) = 0;
	virtual void EnergySplash(const Vector& position, const Vector& direction, bool bExplosive = false) = 0;
	virtual void Ricochet(const Vector& position, const Vector& direction) = 0;
	virtual float Time() = 0;
	virtual bool IsServer() = 0;
	virtual void SuppressEffectsSounds(bool bSuppress) = 0;
};



class CRecipientFilter : public IRecipientFilter
{
public:
	CRecipientFilter();
	virtual ~CRecipientFilter();
	virtual bool IsReliable(void) const;
	virtual int GetRecipientCount(void) const;
	virtual int	 GetRecipientIndex(int slot) const;
	virtual bool IsInitMessage(void) const { return false; };

public:
	void CopyFrom(const CRecipientFilter& src);
	void Reset(void);
	void MakeReliable(void);
	void AddAllPlayers(void);
	void AddRecipientsByPVS(const Vector& origin);
	void AddRecipientsByPAS(const Vector& origin);
	void AddRecipient(CBaseEntity* player);
	void RemoveRecipient(CBaseEntity* player);
	void AddRecipientsByTeam(CBaseEntity* team);
	void RemoveRecipientsByTeam(CBaseEntity* team);
	void UsePredictionRules(void);
	bool IsUsingPredictionRules(void) const;
	bool IgnorePredictionCull(void) const;
	void SetIgnorePredictionCull(bool ignore);
	void AddPlayersFromBitMask(void* playerbits);

	bool m_bReliable;
	bool m_bInitMessage;
	CUtlVector< int > m_Recipients;
	bool m_bUsingPredictionRules;
	bool m_bIgnorePredictionCull;
};

class CEffectsClient : public IEffects
{
public:
	CEffectsClient();
	virtual ~CEffectsClient();

	virtual void Beam(const Vector& Start, const Vector& End, int nModelIndex,
		int nHaloIndex, unsigned char frameStart, unsigned char frameRate,
		float flLife, unsigned char width, unsigned char endWidth, unsigned char fadeLength,
		unsigned char noise, unsigned char red, unsigned char green,
		unsigned char blue, unsigned char brightness, unsigned char speed);
	virtual void Smoke(const Vector& origin, int modelIndex, float scale, float framerate);
	virtual void Sparks(const Vector& position, int nMagnitude = 1, int nTrailLength = 1, const Vector* pvecDir = NULL);
	virtual void Dust(const Vector& pos, const Vector& dir, float size, float speed);
	virtual void MuzzleFlash(const Vector& origin, const QAngle& angles, float fScale, int type);
	virtual void MetalSparks(const Vector& position, const Vector& direction);
	virtual void EnergySplash(const Vector& position, const Vector& direction, bool bExplosive = false);
	virtual void Ricochet(const Vector& position, const Vector& direction);
	virtual float Time();
	virtual bool IsServer();
	virtual void SuppressEffectsSounds(bool bSuppress);

private:
	bool SuppressTE(CRecipientFilter& filter)
	{
		if (!CanPredict())
			return true;

		if (!filter.GetRecipientCount())
		{
			return true;
		}

		return false;
	}

	bool m_bSuppressSound;
};

MAKE_INTERFACE_VERSION(CEffectsClient, EffectsClient, "client.dll", "IEffects001");