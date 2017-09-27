#pragma once
#include <vector>

#if _X86_ || _M_IX86 || _M_IA64 || _M_ARM || _WIN64 || _WIN32
// On CPUs with DOUBLE_PRECISION Hardware-Implementation:
#define decimal double
#else
#define decimal float
#endif

/// <summary>
/// Squash a value with the Sigmoid
/// function (https://en.wikipedia.org/wiki/Sigmoid_function) using
/// doubles (because doubles are being Hardware-implemented -> faster)
/// </summary>
decimal Squash(decimal input);

/// <summary>
/// Rectify a value with the rectified linear unit (ReLU)
/// function (https://en.wikipedia.org/wiki/Rectifier_(neural_networks)) using
/// doubles (because doubles are being Hardware-implemented -> faster)
/// </summary>
decimal Rectify(decimal input);


/// <summary>
/// Calculate the Error of the neural network
/// by given expected output and actual output
/// </summary>
decimal GetError(decimal expected, decimal actual);

/// <summary>
/// Sums up a vector
/// </summary>
decimal Sum(std::vector<decimal>*);