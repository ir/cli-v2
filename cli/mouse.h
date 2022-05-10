#pragma once
#ifndef __MOUSE
#include <Windows.h>
#include <time.h>
#include <vector>
#include <string>
#include "output.h"
enum Mode
{
	MOVE_RELATIVE,
	MOVE_STATIC,
	MOVE_WND
};

struct vec2
{
	int x;
	int y;
};

namespace m_move
{
	void GetWindowPos(int* x, int* y, HWND hWnd);
	void move_click(int sleep);
	void move_relative(vec2 amount);
	void move_static(int x, int y);
	void move_window(int x, int y, bool show, bool click, HWND hWnd);
	void move_return(int x, int y, int mode);
	std::vector<int> m_vecGetPos();
	vec2 mGetPos();
	output::rgb mGetColor(vec2 mpos);
	std::string c_getHex(output::rgb m_color);
}

#endif // !__MOUSE