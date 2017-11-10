#include "Functions.h"
#include <math.h>

double squash(const double value)
{
	return 1 / (1 + exp(-value));
}

double expand(const double squashed)
{
	return log(squashed / (1 - squashed));
}

double squash_derivative(const double value)
{
	return value * (1 - value);
}


// LOGISTIC:
//   float exp = std::pow(EulerConstant, value);
//   return exp / (exp + 1);

// HYPERBOLIC TAN:
//   float expP = std::pow(EulerConstant, value);
//   float expN = std::pow(EulerConstant, -value);
//   return (expP - expN) / (expP + expN);

// SPECIFIC ALGEBRAIC:
//   return (value) / std::sqrt(1 + std::pow(value, 2));

// BRAH:
// ((value - min_A) / max_A - min_A) * (new_max_A - new_min_A) + new_min_A
