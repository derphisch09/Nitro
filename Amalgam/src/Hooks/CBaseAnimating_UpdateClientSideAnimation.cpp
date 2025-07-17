#include "../SDK/SDK.h"

#include "../Features/Animations/Animations.h"
#include "../Features/Resolver/Resolver.h"

MAKE_SIGNATURE(CBaseAnimating_UpdateClientSideAnimation, "client.dll", "48 89 5C 24 ? 57 48 83 EC ? 48 8B D9 E8 ? ? ? ? 48 8B F8 48 85 C0 74 ? 48 8B 00 48 8B CF FF 90 ? ? ? ? 84 C0 75 ? 33 FF 48 3B DF", 0x0);

MAKE_HOOK(CBaseAnimating_UpdateClientSideAnimation, S::CBaseAnimating_UpdateClientSideAnimation(), void, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CBaseAnimating_UpdateClientSideAnimation[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	auto pLocal = H::Entities.GetLocal();
	auto pPlayer = reinterpret_cast<CTFPlayer*>(rcx);

	if ((Vars::Visuals::Removals::Interpolation.Value || F::Resolver.GetAngles(pPlayer)) && !G::UpdatingAnims
		|| pPlayer == pLocal && !pLocal->InCond(TF_COND_HALLOWEEN_KART) && !I::EngineClient->IsPlayingDemo())
		return;

	if (CTFWeaponBase* wep = H::Entities.GetWeapon())
		wep->UpdateAllViewmodelAddons();

	/*CStudioHdr* hdr = pPlayer->GetModelPtr();

	if (!hdr)
		return;

	memcpy(pPlayer->GetCachedBoneData()->Base(), F::Animations.m_LocalBones.data(), sizeof(matrix3x4) * pPlayer->GetCachedBoneData()->Count());

	for (int iter; iter < pPlayer->GetCachedBoneData()->Count(); iter++)
	{
		const matrix3x4& bone = F::Animations.m_LocalBones[iter];

		const Vec3 bone_pos = bone[0][3], bone[1][3], bone[2][3];
		const Vec3 render_origin = pPlayer->GetRenderOrigin() + (bone_pos - F::Animations.m_BoneOrigin);

		matrix3x4& cached_bone = pPlayer->GetCachedBoneData()->Element(iter);

		cached_bone[0][3] = render_origin.x;
		cached_bone[1][3] = render_origin.y;
		cached_bone[2][3] = render_origin.z;
	}

	pPlayer->AttachmentHelper(hdr);*/
	CALL_ORIGINAL(rcx);
}