#include "stdafx.h"
#include "Console.h"

#ifdef linux
#include <sys/ioctl.h>
#else
#include <Windows.h>
#endif

Point::Point(int x, int y)
{
	this->X = x;
	this->Y = y;
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

Point console::get_pos()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return Point(csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y);
}

void console::set_pos(int x, int y)
{
#ifdef linux
	//TODO
#else
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
#endif
}

void console::set_title(std::string title)
{
#ifdef linux

#else
	SetConsoleTitle(s2ws(title).c_str());
#endif
}

#ifndef linux
std::wstring console::s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, nullptr, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}
#endif
