#pragma once
#include <fstream>
#include <bitset>
#include <math.h>

inline uint32_t read_int(std::ifstream &fileStream)
{
	unsigned char bytes[4];
	fileStream.read((char*)bytes, 4);

	return (uint32_t)((bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3]);
}

inline uint16_t read_short(std::ifstream &fileStream)
{
	unsigned char bytes[2];
	fileStream.read((char*)bytes, 2);
	return (uint16_t)((bytes[0] << 8) | bytes[1]);
}

inline uint8_t read_byte(std::ifstream &fileStream)
{
	return (uint8_t)fileStream.get();
}

inline double highest_element(const double* input, const int length)
{
	double highest = 0.0;
	for (int i = 0; i < length; i++)
	{
		if (input[i] > highest) highest = input[i];
	}
	return highest;
}

inline int highest_index(const double* input, const int length)
{
	double highest = 0.0;
	int index = 0;
	for (int i = 0; i < length; i++)
	{
		if (input[i] > highest)
		{
			highest = input[i];
			index = i;
		}
	}
	return index;
}
