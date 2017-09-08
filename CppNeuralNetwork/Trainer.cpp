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
	vector<double>* values = new vector<double>{ 1, 0, 1, 1, 0 };
	vector<double>* weights = new vector<double>{ 1, 1, 1, 1, 0 };
	int output = 1;
	_net->Train(values, weights, output);
}