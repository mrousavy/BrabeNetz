#include "stdafx.h"
#include "Functions.h"
#include <cmath>
const double EulerConstant = std::exp(1.0);

/// <summary>
/// Squash a value with the Sigmoid
/// function (https://en.wikipedia.org/wiki/Sigmoid_function) using
/// floats (Min: -63 | Max: 64)
/// </summary>
float Squash(float value) {
	float exp = std::pow(EulerConstant, value);
	return exp / (exp + 1);
}
