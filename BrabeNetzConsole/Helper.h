#pragma once
#include <fstream>

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
