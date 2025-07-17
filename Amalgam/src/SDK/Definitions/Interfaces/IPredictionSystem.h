#pragma once

#include "Interface.h"

class CBaseEntity;

class IPredictionSystem
{
public:
	IPredictionSystem()
	{
		m_pNextSystem = g_pPredictionSystems;
		g_pPredictionSystems = this;

		m_bSuppressEvent = false;
		m_pSuppressHost = NULL;

		m_nStatusPushed = 0;
	};

	virtual ~IPredictionSystem() {};

	IPredictionSystem* GetNext()
	{
		return m_pNextSystem;
	}

	void SetSuppressEvent(bool state)
	{
		m_bSuppressEvent = state;
	}

	void SetSuppressHost(CBaseEntity* host)
	{
		m_pSuppressHost = host;
	}

	CBaseEntity* GetSuppressHost(void)
	{
		if (DisableFiltering())
		{
			return NULL;
		}

		return m_pSuppressHost;
	}

	bool CanPredict(void) const
	{
		if (DisableFiltering())
		{
			return false;
		}

		return !m_bSuppressEvent;
	}

	void SuppressEvents(bool state)
	{
		IPredictionSystem* sys = g_pPredictionSystems;

		while (sys)
		{
			sys->SetSuppressEvent(state);
			sys = sys->GetNext();
		}
	}

	void SuppressHostEvents(CBaseEntity* host)
	{
		IPredictionSystem* sys = g_pPredictionSystems;

		while (sys)
		{
			sys->SetSuppressHost(host);
			sys = sys->GetNext();
		}
	}

public:
	IPredictionSystem* g_pPredictionSystems;
	IPredictionSystem* m_pNextSystem;
	bool m_bSuppressEvent;
	CBaseEntity* m_pSuppressHost;
	int m_nStatusPushed;

private:
	void Push(void)
	{
		IPredictionSystem* sys = g_pPredictionSystems;

		while (sys)
		{
			sys->_Push();
			sys = sys->GetNext();
		}
	}

	void Pop(void)
	{
		IPredictionSystem* sys = g_pPredictionSystems;

		while (sys)
		{
			sys->_Pop();
			sys = sys->GetNext();
		}
	}

	void _Push(void)
	{
		++m_nStatusPushed;
	}

	void _Pop(void)
	{
		--m_nStatusPushed;
	}

	bool DisableFiltering(void) const
	{
		return (m_nStatusPushed > 0) ? true : false;
	}

	friend class CDisablePredictionFiltering;
};

MAKE_INTERFACE_SIGNATURE(IPredictionSystem, PredictionSystem, "client.dll", "48 89 05 ? ? ? ? 48 8D 05 ? ? ? ? 48 89 05 ? ? ? ? E9 ? ? ? ? CC CC CC CC CC CC CC CC 48 83 EC 28", 0x0, 0);

class CDisablePredictionFiltering
{
public:
	CDisablePredictionFiltering(bool disable = true)
	{
		m_bDisabled = disable;

		if (m_bDisabled)
		{
			I::PredictionSystem->Push();
		}
	}

	~CDisablePredictionFiltering(void)
	{
		if (m_bDisabled)
		{
			I::PredictionSystem->Pop();
		}
	}

private:
	bool m_bDisabled;
};