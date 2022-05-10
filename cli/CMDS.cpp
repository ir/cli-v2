#include "CMDS.h"

void CMDS::print(std::optional<std::string> data)
{
	if (!data.has_value())
		return;
	output::print(output::C_SUCCESS, data.value() + "\n");
}

void CMDS::console::change_title(std::optional<std::string> data)
{
	if (SetConsoleTitleA((LPCSTR)data.value().c_str()))
	{
		output::print(output::C_SUCCESS, "set console title to: " + data.value() + "\n\n");
	}
}


void CMDS::dll::load(std::optional<std::string> data)
{
	std::string option;
	output::print(output::C_INFO, "1. notepad\n2. spotify\n");
	std::getline(std::cin, option);
	char o = option[0];
	switch (o)
	{
	case '1': // notepad
			output::print(output::C_INFO, "loading notepad..\n");
		break;
	case '2': // spotify
			output::print(output::C_INFO, "loading spotify..\n");
		break;
	default:
			output::print(output::C_ERROR, "invalid option\n");
		break;	
	}
}

/*
void CMDS::mouse::move(std::optional<std::string> data)
{
	std::string x; std::string y; int yy = 0;
	for (const auto& c : data.value())
	{
		if (c == ' ')
			yy = 1;
		if (yy == 0)
			x += c;
		else
			y += c;
	}		
	int mx = std::stoi(x);
	int my = std::stoi(y);
		
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.mouseData = 0;
	input.mi.time = 0;
	input.mi.dx = mx;
	input.mi.dy = my;
	input.mi.dwFlags = MOUSEEVENTF_MOVE;
	SendInput(1, &input, sizeof(input));

}
*/