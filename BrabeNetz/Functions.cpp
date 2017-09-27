#include "stdafx.h"
#include "Functions.h"
#include <cmath>
#include <vector>
using namespace std;

#if _X86_ || _M_IX86 || _M_IA64 || _M_ARM || _WIN64 || _WIN32
// On CPUs with DOUBLE_PRECISION Hardware-Implementation:
#define decimal double
#else
#define decimal float
#endif

// The Euler's constant (e) calculated with exp(1)
const decimal EulerConstant = std::exp(1.0);
// Minimum value that's possible as a Squash(..) input parameter
const decimal MinValue = 0;
// Maximum value that's possible as a Squash(..) input parameter
const decimal MaxValue = 1;

/// <summary>
/// Squash a value with the Sigmoid
/// function (https://en.wikipedia.org/wiki/Sigmoid_function) using
/// doubles or floats (depending on compile-architecture)
/// </summary>
decimal Squash(decimal value)
{
	// Squash via BRAH function (squash to -1 .. +1)
	return (value - MinValue) / (MaxValue - MinValue);
}

/// <summary>
/// Rectify a value with the rectified linear unit (ReLU)
/// function (https://en.wikipedia.org/wiki/Rectifier_(neural_networks)) using
/// doubles or floats (depending on compile-architecture)
/// </summary>
decimal Rectify(decimal value)
{
	return fmax(value, 0);
}

/// <summary>
/// Rectify a value with the rectified linear unit (ReLU)
/// function (https://en.wikipedia.org/wiki/Rectifier_(neural_networks)) using
/// doubles (because doubles are being Hardware-implemented -> faster)
/// </summary>
decimal Sum(vector<decimal>* values)
{
	decimal sum = 0;
	for (int i = 0; i < values->size(); i++)
	{
		sum += values->at(i);
	}
	return sum;
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

// BRAH
// ((value - min_A) / max_A - min_A) * (new_max_A - new_min_A) + new_min_A