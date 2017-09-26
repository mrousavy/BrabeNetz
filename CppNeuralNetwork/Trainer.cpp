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
	int size = 2;
	double* values = new double[size] { 1, 1 };
	int output = 1;

	cout << "{ 1, 1 }: ";
	// TODO: TRAIN RETURNS ACCURACY/ERROR
	double result = _net->Train(values, size, output);
	cout << result << endl;

	delete values;
}