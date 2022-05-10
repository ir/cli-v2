#pragma once
#ifndef __OUTPUT
#define __OUTPUT
#include <string>

namespace output
{
	struct rgb
	{
		int r;
		int g;
		int b;
	};
	
	enum type
	{
		C_TEXT = 0,
		C_ERROR,
		C_SUCCESS,
		C_INFO
	};
	
	
	void print(int type, std::string data);

	//void print(rgb color, std::string data);
	
}


#endif // !__OUTPUT



