#pragma once

// Doubles instead of floats because they are hardware implemented on most architectures
//				(_X86_ || _M_IX86 || _M_IA64 || _M_ARM || _WIN64 || _WIN32)

/// <summary>
/// Squash a value with the Sigmoid
/// function (https://en.wikipedia.org/wiki/Sigmoid_function)
/// </summary>
double squash(const double input);

/// <summary>
/// Undo the squash(..) function
/// </summary>
double expand(const double squashed);

/// <summary>
/// Squash a double value with the derivative of the Sigmoid
/// function (https://en.wikipedia.org/wiki/Sigmoid_function)
/// (The input value should be already squashed!)
/// </summary>
double squash_derivative(const double input);
