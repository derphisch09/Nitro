#pragma once

#include "Interface.h"

class CBaseEntity;

class IPredictableList
{
public:
	VIRTUAL_ARGS(GetPredictable, CBaseEntity*, 0, (int slot), this, slot);
	VIRTUAL(GetPredictableCount, int, 1, this);
};

MAKE_INTERFACE_SIGNATURE(IPredictableList, PredictableList, "client.dll", "48 8B 0D ? ? ? ? 48 8B 01 FF 50 08 33 DB 8B F0 85 C0 7E 37 0F 1F 40 00", 0x0, 0);