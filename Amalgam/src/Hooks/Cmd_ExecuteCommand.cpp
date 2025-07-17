#include "../SDK/SDK.h"

#include "../Features/Commands/Commands.h"

MAKE_SIGNATURE(Cmd_ExecuteCommand, "engine.dll", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 44 8B 09", 0x0);

enum cmd_source_t
{
	src_client,
	src_command
};

MAKE_HOOK(Cmd_ExecuteCommand, S::Cmd_ExecuteCommand(), void*, const CCommand& command, cmd_source_t src, int nClientSlot)
{
	if (command.ArgC())
	{
		std::string sCommand = command[0];
		std::deque<std::string> vArgs;

		for (int i = 1; i < command.ArgC(); i++)
			vArgs.push_back(command[i]);

		if (F::Commands.Run(sCommand, vArgs))
			return nullptr;
	}

	return CALL_ORIGINAL(command, src, nClientSlot);
}