#include "Console.h"

#ifdef linux
#include <iostream>
#else
#include <Windows.h>
#endif

void console::set_title(std::string title)
{
	char esc_start[] = { 0x1b, ']', '0', ';', 0 };
	char esc_end[] = { 0x07, 0 };
	std::cout << esc_start << "XTerm Title" << esc_end;
}