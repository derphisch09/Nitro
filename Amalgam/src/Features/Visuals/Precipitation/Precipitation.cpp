#include "Precipitation.h"

ClientClass* CPrecipitation::GetPrecipitationClass()
{
	static ClientClass* pReturn = nullptr;

	if (!pReturn)
	{
		for (auto pClass = I::BaseClientDLL->GetAllClasses(); pClass; pClass = pClass->m_pNext)
		{
			if (pClass->m_ClassID == static_cast<int>(ETFClassID::CPrecipitation))
			{
				pReturn = pClass;
				break;
			}
		}
	}

	return pReturn;
}

void CPrecipitation::Run()
{
	constexpr auto PRECIPITATION_INDEX = (MAX_EDICTS - 1);

	CBaseEntity* pRainEntity = nullptr;
	IClientNetworkable* pRainNetworkable = nullptr;

	if (m_iRainEntityIndex != -1)
	{
		IClientEntity* pClientEntity = I::ClientEntityList->GetClientEntity(m_iRainEntityIndex);

		if (pClientEntity) 
		{
			pRainEntity = pClientEntity->GetBaseEntity();
			pRainNetworkable = pClientEntity->GetClientNetworkable();
		}
		else 
		{
			m_iRainEntityIndex = -1;
		}
	}

	if (!pRainEntity)
	{
		const auto pClass = GetPrecipitationClass();

		if (!pClass || !pClass->m_pCreateFn)
		{
			m_iRainEntityIndex = -1;
			return;
		}

		pRainNetworkable = reinterpret_cast<IClientNetworkable * (__cdecl*)(int, int)>(pClass->m_pCreateFn)(PRECIPITATION_INDEX, 0);

		if (!pRainNetworkable)
		{
			m_iRainEntityIndex = -1;
			return;
		}

		IClientEntity* pClientEntity = I::ClientEntityList->GetClientEntity(PRECIPITATION_INDEX);

		if (!pClientEntity)
		{
			pRainNetworkable->Release();
			m_iRainEntityIndex = -1;
			return;
		}

		pRainEntity = pClientEntity->GetBaseEntity();
		m_iRainEntityIndex = PRECIPITATION_INDEX;

		static auto dwOff = U::NetVars.GetNetVar("CPrecipitation", "m_nPrecipType");

		if (dwOff && pRainEntity)
			*reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(pRainEntity) + dwOff) = Vars::Visuals::World::PrecipitationType.Value - 1;

		pRainNetworkable->PreDataUpdate(DATA_UPDATE_CREATED);
		pRainNetworkable->OnPreDataChanged(DATA_UPDATE_CREATED);

		if (pRainEntity) 
		{
			pRainEntity->m_vecMins() = Vec3(-32767.0f, -32767.0f, -32767.0f);
			pRainEntity->m_vecMaxs() = Vec3(32767.0f, 32767.0f, 32767.0f);
		}

		pRainNetworkable->OnDataChanged(DATA_UPDATE_CREATED);
		pRainNetworkable->PostDataUpdate(DATA_UPDATE_CREATED);
	}
	else
	{
		static auto dwOff = U::NetVars.GetNetVar("CPrecipitation", "m_nPrecipType");

		if (dwOff && pRainEntity)
		{
			int currentType = *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(pRainEntity) + dwOff);
			int desiredType = Vars::Visuals::World::PrecipitationType.Value - 1;

			if (currentType != desiredType)
			{
				*reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(pRainEntity) + dwOff) = desiredType;

				if (pRainNetworkable)
					pRainNetworkable->OnDataChanged(DATA_UPDATE_DATATABLE_CHANGED);
			}
		}
	}
}

void CPrecipitation::Update()
{
	if (!I::EngineClient || !I::ClientState || !I::BaseClientDLL)
	{
		if (IsRaining()) 
			Cleanup();

		return;
	}

	bool bReady = I::EngineClient->IsInGame() && I::EngineClient->IsConnected() && I::ClientState->m_nSignonState == SIGNONSTATE_FULL;

	if (!bReady)
	{
		if (IsRaining()) 
			Cleanup();

		return;
	}

	if (Vars::Visuals::World::PrecipitationType.Value != Vars::Visuals::World::PrecipitationTypeEnum::Off)
	{
		Run();
	}
	else
	{
		if (IsRaining()) 
			Cleanup();
	}
}

void CPrecipitation::Cleanup()
{
	if (m_iRainEntityIndex != -1)
	{
		IClientNetworkable* pRainNetworkable = I::ClientEntityList->GetClientNetworkable(m_iRainEntityIndex);

		if (pRainNetworkable)
			pRainNetworkable->Release();

		m_iRainEntityIndex = -1;
	}
}