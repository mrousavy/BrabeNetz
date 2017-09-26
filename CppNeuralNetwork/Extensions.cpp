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
