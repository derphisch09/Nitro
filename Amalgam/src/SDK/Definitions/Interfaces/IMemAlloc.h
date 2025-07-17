#pragma once

#include "Interface.h"

class IMemAlloc
{
public:
	VIRTUAL_ARGS(Alloc, void*, 1, (size_t nSize), this, nSize);
	VIRTUAL_ARGS(Realloc, void*, 3, (void* pMem, size_t nSize), this, pMem, nSize);
	VIRTUAL_ARGS(Free, void, 5, (void* pMem), this, pMem);
};

MAKE_INTERFACE_NULL(IMemAlloc, MemAlloc);