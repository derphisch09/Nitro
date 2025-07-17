#include "../SDK/SDK.h"
#include "../../Features/Chams/DMEChams.h"

MAKE_SIGNATURE(CMaterial_DeleteIfUnreferenced, "materialsystem.dll", "56 8B F1 83 7E 1C 00 7F 51", 0x0);

MAKE_HOOK(CMaterial_DeleteIfUnreferenced, S::CMaterial_DeleteIfUnreferenced(), void, IMaterial* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CMaterial_DeleteIfUnreferenced[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	//if (ecx) 
	//{
		//if (std::find(F::DMEChams.v_MatListGlobal.begin(), F::DMEChams.v_MatListGlobal.end(), ecx) != F::DMEChams.v_MatListGlobal.end())
			//return;
	//}

	return CALL_ORIGINAL(rcx);
}