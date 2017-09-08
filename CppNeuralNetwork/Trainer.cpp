#include "stdafx.h"
#include "Trainer.h"

// Network instance
Network* _net;


Trainer::Trainer(Network* net)
{
	_net = net;
}


Trainer::~Trainer()
{}

void Trainer::TrainXor()
{
	int* values = new int[2]{ 1, 0 };
	int* weights = new int[2]{ 1, 1 };
	int output = 1;
	_net->Train(values, weights, output);
}