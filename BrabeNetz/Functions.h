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
/// Undo the squash(..) function
/// </summary>
DECIMAL expand(const DECIMAL squashed);

/// <summary>
/// Squash a value with the derivative of the Sigmoid
/// function (https://en.wikipedia.org/wiki/Sigmoid_function) using
/// doubles (because doubles are being Hardware-implemented -> faster)
/// </summary>
DECIMAL squash_derivative(const DECIMAL input);

/// <summary>
/// Derivative of the sigmoid transfer function
/// (used for error calculation)
/// </summary>
DECIMAL transfer_derivative(const DECIMAL input);

/// <summary>
/// Rectify a value with the rectified linear unit (ReLU)
/// function (https://en.wikipedia.org/wiki/Rectifier_(neural_networks)) using
/// doubles (because doubles are being Hardware-implemented -> faster)
/// </summary>
DECIMAL rectify(const DECIMAL input);

/// <summary>
/// Calculate the distance between two input arrays
/// via the Euclidean distance function. For the neural
/// network this function takes the expected output as 'x',
/// and the actual output as 'y', length being the size of
/// those arrays.
/// </summary>
DECIMAL euclidean_dist(DECIMAL* x, DECIMAL* y, int length);

/// <summary>
/// Calculate the cost/loss of two input arrays
/// </summary>
DECIMAL cost_func(DECIMAL* expected, DECIMAL* actual, int length);

/// <summary>
/// Calculate the first derivative of the cost/loss function
/// </summary>
DECIMAL cost_derivative(DECIMAL* expected, DECIMAL* actual, int length);

/// <summary>
/// Calculate the Error of the output layer 
///	in the neural network by given expected 
/// output and actual output
/// </summary>
DECIMAL get_error(const DECIMAL expected, const DECIMAL actual);

/// <summary>
/// Calculate the Error of any layer
///	in the neural network by given expected 
/// output, actual output
/// </summary>
DECIMAL get_error(const DECIMAL neuron_value, const DECIMAL* next_errors,
				  const DECIMAL* next_weights, const int next_layer_size);

/// <summary>
/// Sums up values in a vector
/// </summary>
DECIMAL sum(std::vector<DECIMAL>& values);

/// <summary>
/// Sums up values in an array with size `length`
/// </summary>
DECIMAL sum(DECIMAL* values, const int length);
