#include "CMDS.h"

void CMDS::print(std::optional<std::string> data)
{
	if (!data.has_value())
		return;
	output::print(output::C_SUCCESS, data.value() + "\n");
}