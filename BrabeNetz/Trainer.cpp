#include "stdafx.h"
#include "Trainer.h"
#include <iostream>

#define TRAIN_TIMES_EACH 1000
#define TRAIN_POSSIBILITIES 4

void trainer::train_xor(network& net)
{
	const int size = 2;
	double* values;
	double* expected = new double[1];

	for (int i = 0; i < TRAIN_TIMES_EACH * TRAIN_POSSIBILITIES; i++)
		// Loop TRAIN_TIMES_EACH (1000) * TRAIN_POSSIBILITIES (4)
	{
		switch (i % 4) // Train all 4 cases alternately
		{
			case 0:
				values = new double[size] { 0, 0 };
				expected[0] = 0;
				break;
			case 1:
				values = new double[size] { 1, 0 };
				expected[0] = 1;
				break;
			case 2:
				values = new double[size] { 0, 1 };
				expected[0] = 1;
				break;
			case 3:
			default:
				values = new double[size] { 1, 1 };
				expected[0] = 0;
				break;
		}
		const double learn_rate = 1.0 / (i + 1.0);
		net.set_learnrate(learn_rate);

		const double result = net.train(values, size, expected);

		//if (i % 4 == 0)
			cout << "{ " << values[0] << ", " << values[1] << " }: " << expected[0] << " | " << result << " @ l_r:" << learn_rate <<  endl;

		// Cleanup
		delete[] values;
	}
	delete[] expected;
}