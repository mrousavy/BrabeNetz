#pragma once
#include "Network.h"

// Use a constant learn rate (LEARN_RATE) for training instead of small decreasing one
#define CONST_LEARN_RATE true
// Learn rate to use if CONST_LEARN_RATE is true
#define DEFAULT_LEARN_RATE 0.5
// Print the input, expected and actual output to console (that's hella slow!)
#define PRINT_OUTPUT false

/// <summary>
/// A Neuronal Network Trainer supporting bools
/// </summary>
class trainer
{
public:
	// Teach the network XOR switches
	static void train_xor(network& net, int train_times);
};
