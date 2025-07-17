#pragma once

#include "CBaseEntity.h"

class CTEFireBullets
{
public:
	uintptr_t vtable;
	char _pad0[16];
	int m_iPlayer;
	Vector m_vecOrigin;
	QAngle m_vecAngles;
	int m_iWeaponID;
	int m_iMode;
	int m_iSeed;
	float m_flSpread;
	bool m_bCritical;
};