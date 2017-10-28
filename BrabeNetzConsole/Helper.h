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

inline std::bitset<8> array_to_bits_rounded(const double* input, const int length)
{
	std::bitset<8> bits{};
	for (int i = 0; i < length; i++)
	{
		// TODO:
		bits <<= 1;
		double rounded = round(input[i]);
		std::bitset<8> bits_tmp{ (unsigned long)rounded };
		bits |= bits_tmp;
	}
	return bits;
}
