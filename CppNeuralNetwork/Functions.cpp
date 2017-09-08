#include "stdafx.h"
#include "Functions.h"
#include <cmath>

#if _X86_ || _M_IX86 || _M_IA64 || _M_ARM || _WIN64 || _WIN32

// On CPUs with DOUBLE_PRECISION Hardware-Implementation:
const double EulerConstant = std::exp(1.0);
/// <summary>
/// Squash a value with the Sigmoid
/// function (https://en.wikipedia.org/wiki/Sigmoid_function) using
/// double
/// </summary>
double Squash(double value)
{
	double expP = std::pow(EulerConstant, value);
	double expN = std::pow(EulerConstant, -value);
	return (expP - expN) / (expP + expN);
}

#else

// On CPUs with DOUBLE_PRECISION Software-Implementation:
const float EulerConstant = std::exp((float)1.0);
/// <summary>
/// Squash a value with the Sigmoid
/// function (https://en.wikipedia.org/wiki/Sigmoid_function) using
/// floats (Min: -63 | Max: 64)
/// </summary>
float Squash(float value)
{
	float expP = std::pow(EulerConstant, value);
	float expN = std::pow(EulerConstant, -value);
	return (expP - expN) / (expP + expN);
}

#endif


// LOGISTIC:
//   float exp = std::pow(EulerConstant, value);
//   return exp / (exp + 1);

// HYPERBOLIC TAN:
//   double expP = std::pow(EulerConstant, value);
//   double expN = std::pow(EulerConstant, -value);
//   return (expP - expN) / (expP + expN);

// SPECIFIC ALGEBRAIC
//   return (value) / std::sqrt(1 + std::pow(value, 2));