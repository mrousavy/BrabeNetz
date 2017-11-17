#pragma once
#include <string>
#include <iostream>

using namespace std;

namespace console
{
	inline void set_title(const string title)
	{
#ifdef linux
		char esc_start[] = { 0x1b, ']', '0', ';', 0 };
		char esc_end[] = { 0x07, 0 };
		cout << esc_start << title << esc_end;
#else
		SetConsoleTitle(s2_ws(title).c_str());
#endif
	}

#ifndef linux
	inline std::wstring s2_ws(const std::string& input)
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
};
