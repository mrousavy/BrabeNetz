#pragma once

#if _X86_ || _M_IX86 || _M_IA64 || _M_ARM || _WIN64 || _WIN32
// On CPUs with DOUBLE_PRECISION Hardware-Implementation:
	/// <summary>
	/// Squash a value with the Sigmoid
	/// function (https://en.wikipedia.org/wiki/Sigmoid_function) using
	/// doubles
	/// </summary>
double Squash(double);
#else
// On CPUs with DOUBLE_PRECISION Software-Implementation:
	/// <summary>
	/// Squash a value with the Sigmoid
	/// function (https://en.wikipedia.org/wiki/Sigmoid_function) using
	/// floats (Min: -63 | Max: 64)
	/// </summary>
float Squash(float);
#endif
