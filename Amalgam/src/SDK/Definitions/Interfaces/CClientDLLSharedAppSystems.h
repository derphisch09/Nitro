#pragma once

#include "Interface.h"

class CClientDLLSharedAppSystems
{
public:
	virtual int	Count() = 0;
	virtual char const* GetDllName(int idx) = 0;
	virtual char const* GetInterfaceName(int idx) = 0;
};

MAKE_INTERFACE_VERSION(CClientDLLSharedAppSystems, ClientDLLSharedAppSystems, "client.dll", "VClientDllSharedAppSystems001");