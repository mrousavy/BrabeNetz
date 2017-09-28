#pragma once
#include "Network.h"


/// <summary>
/// A Neuronal Network Trainer supporting bools
/// </summary>
class trainer
{
public:
	explicit trainer(network*);
	~trainer();

	// Teach the network XOR switches
	void train_xor();
};

