#include "../SDK/SDK.h"

MAKE_SIGNATURE(CBasePlayer_CalcDeathCamView, "client.dll", "48 8B C4 48 89 58 20 55 56 57 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 C8 33 FF", 0x0);

MAKE_HOOK(CBasePlayer_CalcDeathCamView, S::CBasePlayer_CalcDeathCamView(), void, void* rcx, Vector& eyeOrigin, QAngle& eyeAngles, float& fov)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CBasePlayer_CalcDeathCamView[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx, eyeOrigin, eyeAngles, fov);
#endif

	CALL_ORIGINAL(rcx, eyeOrigin, eyeAngles, fov);
	fov = Vars::Visuals::UI::FieldOfView.Value;
}