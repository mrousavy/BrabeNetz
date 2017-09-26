#pragma once
#include <vector>

class Extensions
{
public:
	// Convert a vector to an array of type T
	template <typedef T>
	static T ToArray(std::vector<T> input);
};
