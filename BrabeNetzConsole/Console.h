#pragma once
#include <string>

struct point
{
	point(int x, int y);
	int x;
	int y;
};

namespace console
{
	int get_width();
	int get_height();
	point get_pos();
	void set_pos(int x, int y);
	void set_title(std::string title);

#ifndef linux
	std::wstring s2_ws(const std::string& input);
#endif
};
