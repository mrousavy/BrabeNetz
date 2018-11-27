#include "stdafx.h"
#include "Console.h"

#if defined(linux) || defined(__linux__)
#include <sys/ioctl.h>
#elif _WIN32
#include <Windows.h>
#elif __APPLE__
// TODO: Apple
#endif

point::point(int x, int y)
{
	this->x = x;
	this->y = y;
}

int console::get_width()
{
#if defined(linux) || defined(__linux__)
	struct winsize size;
	ioctl(1, TIOCGWINSZ, &size);
	return size.ws_row;
#elif _WIN32
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
#elif __APPLE__
	return 0;
#endif
}

int console::get_height()
{
#ifdef linux
	struct winsize size;
	ioctl(1, TIOCGWINSZ, &size);
	return size.ws_col;
#elif _WIN32
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#elif __APPLE__
	return 0;
#endif
}

point console::get_pos()
{
#ifdef linux
    return {0, 0};
#elif _WIN32
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return point(csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y);
#elif __APPLE__
	return {0, 0};
#endif
}

void console::set_pos(const int x, const int y)
{
#ifdef linux
	// TODO: Linux
#elif _WIN32
	const HWND console_window = GetConsoleWindow();
	SetWindowPos(console_window, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
#elif __APPLE__
	// TODO: Apple
#endif
}

void console::set_title(const std::string title)
{
#ifdef linux
	// TODO: Linux
#elif _WIN32
	SetConsoleTitle(s2_ws(title).c_str());
#elif __APPLE__
	// TODO: Apple
#endif
}

#ifdef _WIN32
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
