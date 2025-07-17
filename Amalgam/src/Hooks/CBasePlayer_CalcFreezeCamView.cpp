#include "../SDK/SDK.h"

MAKE_SIGNATURE(CBasePlayer_CalcFreezeCamView, "client.dll", "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 01 4D 8B F1", 0x0);

MAKE_HOOK(CBasePlayer_CalcFreezeCamView, S::CBasePlayer_CalcFreezeCamView(), void, void* rcx, Vector& eyeOrigin, QAngle& eyeAngles, float& fov)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CBasePlayer_CalcFreezeCamView[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, eyeOrigin, eyeAngles, fov);
#endif

	CALL_ORIGINAL(rcx, eyeOrigin, eyeAngles, fov);
	fov = Vars::Visuals::UI::FieldOfView.Value;
}