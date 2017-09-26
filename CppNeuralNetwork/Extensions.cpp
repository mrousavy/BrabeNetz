#include "stdafx.h"
#include "Extensions.h"


template<typedef T>
inline T* Extensions::ToArray(std::vector<T> input)
{
	T* t = new T[input->size()];
	for (int i = 0; i < input->size(); i++)
	{
		t[i] = input->at(i);
	}
	return t;
}


template<typedef T>
inline std::vector<T> Extensions::ToVector(T* input, int length)
{
	std::vector<T> v = new std::vector<T>();
	for (int i = 0; i < length; i++)
	{
		v.push_back(input[i]);
	}
	return t;
}
