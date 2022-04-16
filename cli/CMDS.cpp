#include "CMDS.h"

void CMDS::print(std::optional<std::string> data)
{
	if (!data.has_value())
		return;
	output::print(output::C_TEXT, data.value() + "\n");
}