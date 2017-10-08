#pragma once
#include <vector>

/// <summary>
/// Squash a value with the Sigmoid
/// function (https://en.wikipedia.org/wiki/Sigmoid_function) using
/// doubles (because doubles are being Hardware-implemented -> faster)
/// </summary>
double squash(const double input);

/// <summary>
/// Undo the squash(..) function
/// </summary>
double expand(const double squashed);

/// <summary>
/// Squash a value with the derivative of the Sigmoid
/// function (https://en.wikipedia.org/wiki/Sigmoid_function) using
/// doubles (because doubles are being Hardware-implemented -> faster)
/// </summary>
double squash_derivative(const double input);