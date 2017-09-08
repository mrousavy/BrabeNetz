#pragma once

#if _WIN64 || _WIN32
/// <summary>
/// Squash a value with the Sigmoid
/// function (https://en.wikipedia.org/wiki/Sigmoid_function) using
/// doubles
/// </summary>
double Squash(double);
#else
/// <summary>
/// Squash a value with the Sigmoid
/// function (https://en.wikipedia.org/wiki/Sigmoid_function) using
/// floats (Min: -63 | Max: 64)
/// </summary>
float Squash(float);
#endif
