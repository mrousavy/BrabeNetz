#include "stdafx.h"
#include "Console.h"

#ifdef linux
#include <sys/ioctl.h>
#else
#include <Windows.h>
#endif

point::point(int x, int y)
{
	this->x = x;
	this->y = y;
}

int console::get_width()
{
#ifdef linux
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	return size.ws_row;
#else
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
#endif
}

int console::get_height()
{
#ifdef linux
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	return size.ws_col;
#else
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#endif
}

point console::get_pos()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return point(csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y);
}

void console::set_pos(const int x, const int y)
{
#ifdef linux
	//TODO
#else
	const HWND console_window = GetConsoleWindow();
	SetWindowPos(console_window, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
#endif
}

void console::set_title(const std::string title)
{
#ifdef linux

#else
	SetConsoleTitle(s2_ws(title).c_str());
#endif
}

#ifndef linux
std::wstring console::s2_ws(const std::string& s)
{
	const int slength = static_cast<int>(s.length()) + 1;
	const int len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, nullptr, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}
#endif
