#pragma once
#include <vector>

class Extensions
{
public:
	// Convert a vector to an array of type T
	template <typedef T>
	static T ToArray(std::vector<T> input);
	// Convert an array to a vector of type T
	template <typedef T>
	static std::vector<T> ToVector(T* input, int length);
};
