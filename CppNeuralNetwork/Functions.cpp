#include "stdafx.h"
#include "Functions.h"
#include <cmath>

#if _X86_ || _M_IX86 || _M_IA64 || _M_ARM || _WIN64 || _WIN32
// On CPUs with DOUBLE_PRECISION Hardware-Implementation:
#define float double
#endif

// On CPUs with DOUBLE_PRECISION Hardware-Implementation:
const float EulerConstant = std::exp(1.0);
/// <summary>
/// Squash a value with the Sigmoid
/// function (https://en.wikipedia.org/wiki/Sigmoid_function) using
/// doubles or floats (depending on compile-architecture)
/// </summary>
float Squash(float value)
{
	float expP = std::pow(EulerConstant, value);
	float expN = std::pow(EulerConstant, -value);
	return (expP - expN) / (expP + expN);
}

/// <summary>
/// Rectify a value with the rectified linear unit (ReLU)
/// function (https://en.wikipedia.org/wiki/Rectifier_(neural_networks)) using
/// doubles or floats (depending on compile-architecture)
/// </summary>
float Rectify(float value)
{
	return fmax(value, 0);
}


// LOGISTIC:
//   float exp = std::pow(EulerConstant, value);
//   return exp / (exp + 1);

// HYPERBOLIC TAN:
//   float expP = std::pow(EulerConstant, value);
//   float expN = std::pow(EulerConstant, -value);
//   return (expP - expN) / (expP + expN);

// SPECIFIC ALGEBRAIC
//   return (value) / std::sqrt(1 + std::pow(value, 2));