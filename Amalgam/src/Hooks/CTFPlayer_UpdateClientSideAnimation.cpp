#include "../../SDK/SDK.h"

#include "../Features/CFG.h"

MAKE_SIGNATURE(CTFPlayer_UpdateClientSideAnimation, "client.dll", "48 89 5C 24 ? 57 48 83 EC 30 48 8B D9 E8 ? ? ? ? 48 8B F8 48 85 C0 74 10", 0x0);

MAKE_HOOK(CTFPlayer_UpdateClientSideAnimation, S::CTFPlayer_UpdateClientSideAnimation(), void, CTFPlayer* ecx)
{
	if (CFG::Misc_Accuracy_Improvements)
	{
		if (const auto pLocal = H::Entities->GetLocal())
		{
			if (ecx == pLocal)
			{
				if (!pLocal->InCond(TF_COND_HALLOWEEN_KART))
				{
					if (const auto pWeapon = H::Entities->GetWeapon())
					{
						pWeapon->UpdateAllViewmodelAddons();
					}

					return;
				}

				CALL_ORIGINAL(ecx);
			}
		}

		if (!G::bUpdatingAnims)
			return;
	}

	CALL_ORIGINAL(ecx);
}
