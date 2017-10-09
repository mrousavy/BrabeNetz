#include "stdafx.h"
#include "Information.h"

#ifdef _WIN32 || _WIN64
#include <Windows.h>

int Information::cpu_speed()
{
	LARGE_INTEGER* i = new LARGE_INTEGER();
	BOOL success = QueryPerformanceFrequency(i);
	return (int)i->QuadPart;
}
#else
#include <ifstream>

int Information::cpu_speed()
{
	// TODO: Read /proc/cpuinfo
	return 0;
}
#endif