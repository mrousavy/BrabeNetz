#pragma once
#include <vector>

namespace extensions
{
	// Convert a vector to an array of type T
	template <typename T>
	T* to_array(std::vector<T>& input)
	{
		return input.data(); // > C++ 11
	}
};
