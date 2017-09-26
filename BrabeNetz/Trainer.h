#pragma once
#include "Network.h"


/// <summary>
/// A Neuronal Network Trainer supporting bools
/// </summary>
class Trainer
{
public:
	Trainer(Network*);
	~Trainer();

	// Teach the network XOR switches
	void TrainXor();
};

