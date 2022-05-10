#include "mouse.h"

// converts to hex
std::string m_move::c_getHex(output::rgb m_color)
{
	char cString[8];
	snprintf(cString, sizeof(cString), "%x%x%x", m_color.r, m_color.g, m_color.b);
	return cString;
}

// gets color of a pixel
output::rgb m_move::mGetColor(vec2 mpos)
{
	HDC dc = GetDC(NULL);
	output::rgb colorrgb;
	COLORREF color = GetPixel(dc, mpos.x, mpos.y);
	colorrgb.r = GetRValue(color); colorrgb.g = GetGValue(color); colorrgb.b = GetBValue(color);
	ReleaseDC(NULL, dc);
	return colorrgb;
}

void m_move::move_relative(vec2 amount)
{
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.mouseData = 0;
	input.mi.time = 0;
	input.mi.dx = amount.x;
	input.mi.dy = amount.y;
	input.mi.dwFlags = MOUSEEVENTF_MOVE;
	SendInput(1, &input, sizeof(input));
}