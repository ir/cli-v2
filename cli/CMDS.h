#pragma once
#ifndef __CMDS
#define __CMDS
#include <iostream>
#include <string>
#include <optional>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include "output.h"
#include "mouse.h"

namespace CMDS
{
	void print(std::optional<std::string> data);
	namespace console
	{
		void change_title(std::optional<std::string> data);
	}
	namespace dll
	{
		void load(std::optional<std::string> data);
		
	}
	namespace mouse
	{
		void move(std::optional<std::string> data);
	}
}

#endif // !__CMDS




