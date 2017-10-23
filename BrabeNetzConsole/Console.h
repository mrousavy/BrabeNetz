#pragma once
#include <string>

struct Point
{
public:
	Point(int x, int y);
	int X;
	int Y;
};

class console
{
public:
	static int get_width();
	static int get_height();
	static Point get_pos();
	static void set_pos(int x, int y);
	static void set_title(std::string title);
private:
	#ifndef linux
	static std::wstring s2ws(const std::string& input);
	#endif
};

