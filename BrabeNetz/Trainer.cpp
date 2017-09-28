#include "stdafx.h"
#include "Trainer.h"
#include <iostream>

#define TRAIN_TIMES_EACH 1000
#define TRAIN_POSSIBILITIES 4

// Network instance
network* _net;


trainer::trainer(network* net)
{
	_net = net;
}


trainer::~trainer()
{}

void trainer::train_xor()
{
	int size = 2;
	double* values;
	int expected;

	for (int i = 0; i < TRAIN_TIMES_EACH * TRAIN_POSSIBILITIES; i++) // Loop TRAIN_TIMES_EACH (1000) * TRAIN_POSSIBILITIES (4)
	{
		switch (i % 4) // Train all 4 cases alternately
		{
			case 0:
				values = new double[size] { 0, 0 };
				expected = 0;
				break;
			case 1:
				values = new double[size] { 1, 0 };
				expected = 1;
				break;
			case 2:
				values = new double[size] { 0, 1 };
				expected = 1;
				break;
			case 3:
			default:
				values = new double[size] { 1, 1 };
				expected = 0;
				break;
		}
		double result = _net->train(values, size, expected);
		cout << "{ " << values[0] << ", " << values[1] << " }: " << expected << " | " << result << endl;

		// Cleanup
		delete[] values;
	}
}