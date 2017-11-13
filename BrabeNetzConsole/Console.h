#pragma once
#include <string>

struct Point
{
public:
	Point(int x, int y);
	int X;
	int Y;
};

namespace console
{
	int get_width();
	int get_height();
	Point get_pos();
	void set_pos(int x, int y);
	void set_title(std::string title);

#ifndef linux
	std::wstring s2ws(const std::string& input);
#endif
};
