#pragma once
#include <vector>

#if _X86_ || _M_IX86 || _M_IA64 || _M_ARM || _WIN64 || _WIN32
// On CPUs with DOUBLE_PRECISION Hardware-Implementation:

/// <summary>
/// Squash a value with the Sigmoid
/// function (https://en.wikipedia.org/wiki/Sigmoid_function) using
/// doubles (because doubles are being Hardware-implemented -> faster)
/// </summary>
double Squash(double);

/// <summary>
/// Rectify a value with the rectified linear unit (ReLU)
/// function (https://en.wikipedia.org/wiki/Rectifier_(neural_networks)) using
/// doubles (because doubles are being Hardware-implemented -> faster)
/// </summary>
double Rectify(double);

/// <summary>
/// Sums up a vector
/// </summary>
double Sum(std::vector<double>*);

#else
// On CPUs with DOUBLE_PRECISION Software-Implementation:

/// <summary>
/// Squash a value with the Sigmoid
/// function (https://en.wikipedia.org/wiki/Sigmoid_function) using
/// floats (because doubles are being Software-implemented -> slower)
/// </summary>
float Squash(float);

/// <summary>
/// Rectify a value with the rectified linear unit (ReLU)
/// function (https://en.wikipedia.org/wiki/Rectifier_(neural_networks)) using
/// floats (because doubles are being Software-implemented -> slower)
/// </summary>
float Rectify(float);

#endif