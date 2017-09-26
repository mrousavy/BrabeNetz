#pragma once
#include <vector>

class Extensions
{
public:
	// Convert a vector to an array of type T
	template <typename T>
	static T* ToArray(std::vector<T> input);
	// Convert an array to a vector of type T
	template <typename T>
	static std::vector<T> ToVector(T* input, int length);
};

template<typename T>
inline T* Extensions::ToArray(std::vector<T> input)
{
	T* t = new T[input->size()];
	for (int i = 0; i < input->size(); i++)
	{
		t[i] = input->at(i);
	}
	return t;
}


template<typename T>
inline std::vector<T> Extensions::ToVector(T* input, int length)
{
	std::vector<T> v = new std::vector<T>();
	for (int i = 0; i < length; i++)
	{
		v.push_back(input[i]);
	}
	return t;
}

