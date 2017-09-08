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

void Trainer::TrainXor() {
	int* arr = new int[2]{ 1,0 };
	_net->Train(arr);
}