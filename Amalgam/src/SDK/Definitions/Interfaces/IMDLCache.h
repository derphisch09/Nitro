#pragma once

#include "Interface.h"

class IMDLCache 
{
public:
	VIRTUAL(BeginLock, void, 25, this);
	VIRTUAL(EndLock, void, 26, this);
};

MAKE_INTERFACE_VERSION(IMDLCache, MDLCache, "datacache.dll", "MDLCache004");