#include "output.h"


void output::print(int type, std::string data)
{
	rgb color;
	switch (type)
	{
	case C_TEXT: // typical text color
		color = { 219, 244, 240 } ;
		break;
	case C_ERROR: // error text color
		color = { 255,204,203 };
		break;
	case C_SUCCESS: // success text color
		color = { 199,237,220 };
		break;
	case C_INFO: // info text color
		color = { 127,185,188 };
		break;
	default: 
		color = { 238, 235, 226 };
		break;
	}
	printf("\033[38;2;%d;%d;%dm%s\033[0m", color.r, color.g, color.b, data.c_str());
}

/*
template <typename T>
void output::print(rgb color, T data)
{
	std::string d = std::to_string(data);
	printf("\033[38;2;%d;%d;%dm%s\033[0m", color.r, color.g, color.b, d.c_str());
}
*/