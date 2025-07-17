#pragma once

#include "Interface.h"

class IDemoRecorder
{
public:
	VIRTUAL(IsRecording, bool, 4, this);
	VIRTUAL_ARGS(RecordUserInput, bool, 9, (int command_number), this, command_number);
};

MAKE_INTERFACE_SIGNATURE(IDemoRecorder, DemoRecorder, "engine.dll", "48 8B 0D ? ? ? ? 8D 56", 0x0, 0);