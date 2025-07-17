#pragma once

#include "Interface.h"
#include "../Definitions.h"
#include "../Main/KeyValues.h"

class IFileSystem
{
public:
	VIRTUAL_ARGS(LoadKeyValues, bool, 76, (KeyValues& head, KeyValuesPreloadType_t type, const char* filename, const char* pPathID = 0), this, head, type, filename, pPathID);
};

MAKE_INTERFACE_SIGNATURE(IFileSystem, FileSystem, "client.dll", "48 8B 0D ? ? ? ? 4C 8D 05 ? ? ? ? 48 83 C1 ? 48 8D 94 24 ? ? ? ? 45 33 C9", 0x0, 0);