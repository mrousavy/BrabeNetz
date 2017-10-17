#pragma once
#include "Network.h"


/// <summary>
/// A Neuronal Network Trainer supporting bools
/// </summary>
class trainer
{
public:
	// Teach the network XOR switches
	static void train_xor(network& net);
};
