#pragma once
#include <vector>

class extensions
{
public:
	// Convert a vector to an array of type T
	template <typename T>
	static T* to_array(std::vector<T>& input);
	// Convert an array to a vector of type T
	template <typename T>
	static std::vector<T> to_vector(T* input, const int length);
	// Convert an array to a vector of type T
	template <typename T>
	static std::vector<T> to_vector(T* input);
};

template <typename T>
T* extensions::to_array(std::vector<T>& input)
{
	return input.data(); // > C++ 11
}


template <typename T>
std::vector<T> extensions::to_vector(T* input, const int length)
{
	std::vector<T> v(*input, length);
	return v;
}

template <typename T>
std::vector<T> extensions::to_vector(T* input)
{
	std::vector<int> v(input, input + sizeof input / sizeof input[0]);
	return v;
}