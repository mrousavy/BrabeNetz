#include "stdafx.h"
#include "Functions.h"
#include <cmath>

#if _WIN64 || _WIN32
// On x86 CPUs:
	const double EulerConstant = std::exp(1.0);
	/// <summary>
	/// Squash a value with the Sigmoid
	/// function (https://en.wikipedia.org/wiki/Sigmoid_function) using
	/// double
	/// </summary>
	double Squash(double value) {
		double exp = std::pow(EulerConstant, value);
		return exp / (exp + 1);
	}
#else
// On other CPUs:
	const float EulerConstant = std::exp(1.0);
	/// <summary>
	/// Squash a value with the Sigmoid
	/// function (https://en.wikipedia.org/wiki/Sigmoid_function) using
	/// floats (Min: -63 | Max: 64)
	/// </summary>
	float Squash(float value) {
		float exp = std::pow(EulerConstant, value);
		return exp / (exp + 1);
	}
#endif