#pragma once
#include <vector>

class extensions
{
public:
	// Convert a vector to an array of type T
	template <typename T>
	static T* to_array(std::vector<T> input);
	// Convert an array to a vector of type T
	template <typename T>
	static std::vector<T> to_vector(T* input, const int length);
};

template<typename T>
inline T* extensions::to_array(std::vector<T> input)
{
	T* t = new T[input->size()];
	for (int i = 0; i < input->size(); i++)
	{
		t[i] = input->at(i);
	}
	return t;
}


template<typename T>
inline std::vector<T> extensions::to_vector(T* input, const int length)
{
	std::vector<T> v;
	for (int i = 0; i < length; i++)
	{
		v.push_back(input[i]);
	}
	return v;
}

