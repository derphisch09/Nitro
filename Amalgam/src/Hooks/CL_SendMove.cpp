#include "../SDK/SDK.h"
#include"../Features/NoSpread/NoSpreadHitscan/NoSpreadHitscan.h"

MAKE_SIGNATURE(CL_SendMove, "engine.dll", "55 8B EC 83 EC 0C 83 3D ? ? ? ? ? 0F 8C ? ? ? ? 8B 0D ? ? ? ? 8B 01 8B 40 54 FF D0 D9 5D F8 B9 ? ? ? ? E8 ? ? ? ? D9 5D FC F3 0F 10 45", 0x0);

MAKE_HOOK(CL_SendMove, S::CL_SendMove(), void, void* rcx)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CL_SendMove[DEFAULT_BIND])
		return CALL_ORIGINAL(rcx);
#endif

	F::NoSpreadHitscan.AskForPlayerPerf();

	byte data[4000];
	CLC_Move msg;

	const int nextcommandnr = I::ClientState->lastoutgoingcommand + I::ClientState->chokedcommands + 1;

	msg.m_DataOut.StartWriting(data, sizeof(data));
	msg.m_nNewCommands = std::clamp(1 + I::ClientState->chokedcommands, 0, MAX_NEW_COMMANDS);

	const int extraCommands = I::ClientState->chokedcommands + 1 - msg.m_nNewCommands;
	const int backupCommands = std::max(2, extraCommands);

	msg.m_nBackupCommands = std::clamp(backupCommands, 0, MAX_BACKUP_COMMANDS);

	const int numcmds = msg.m_nNewCommands + msg.m_nBackupCommands;

	int from = -1;
	bool bOK = true;

	for (int to = nextcommandnr - numcmds + 1; to <= nextcommandnr; to++)
	{
		const bool isnewcmd = to >= nextcommandnr - msg.m_nNewCommands + 1;
		bOK = bOK && I::BaseClientDLL->WriteUsercmdDeltaToBuffer(&msg.m_DataOut, from, to, isnewcmd);
		from = to;
	}

	if (bOK)
	{
		if (extraCommands > 0)
			I::ClientState->m_NetChannel->m_nChokedPackets -= extraCommands;

		U::Memory.GetVirtual<bool>(PVOID, INetMessage* msg, bool, bool)>(I::ClientState->m_NetChannel, 37)(I::ClientState->m_NetChannel, &msg, false, false);

		F::Ticks->m_iShiftedTicks -= I::ClientState->chokedcommands + 1;
		F::Ticks->m_iShiftedTicks = std::max(0, F::Ticks->m_iShiftedTicks);
	}
}