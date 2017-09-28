#pragma once
#include <vector>

#if _X86_ || _M_IX86 || _M_IA64 || _M_ARM || _WIN64 || _WIN32
// On CPUs with DOUBLE_PRECISION Hardware-Implementation:
#define DECIMAL double
#else
#define DECIMAL float
#endif

/// <summary>
/// Squash a value with the Sigmoid
/// function (https://en.wikipedia.org/wiki/Sigmoid_function) using
/// doubles (because doubles are being Hardware-implemented -> faster)
/// </summary>
DECIMAL squash(const DECIMAL input);

/// <summary>
/// Rectify a value with the rectified linear unit (ReLU)
/// function (https://en.wikipedia.org/wiki/Rectifier_(neural_networks)) using
/// doubles (because doubles are being Hardware-implemented -> faster)
/// </summary>
DECIMAL rectify(const DECIMAL input);

/// <summary>
/// Calculate the Error of the output layer 
///	in the neural network by given expected 
/// output and actual output
/// </summary>
DECIMAL get_error(const DECIMAL expected, const DECIMAL actual);

/// <summary>
/// Calculate the Error of any layer
///	in the neural network by given expected 
/// output and actual output
/// </summary>
DECIMAL get_error(const DECIMAL neuron_value, const DECIMAL total_weights);

/// <summary>
/// Sums up a vector
/// </summary>
DECIMAL sum(std::vector<DECIMAL>*);