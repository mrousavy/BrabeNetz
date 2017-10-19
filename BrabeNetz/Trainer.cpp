#include "stdafx.h"
#include "Trainer.h"
#include <iostream>

void trainer::train_xor(network& net, const int train_times)
{
	const int size = 2;
	double* values;
	double* expected = new double[1];

	for (int i = 0; i < train_times * 4; i++) // Loop train_times (1000) * possibilities for XOR (4)
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

		#if !CONST_LEARN_RATE
		const double learn_rate = 1.0 / (i + 1.0);
		net.set_learnrate(learn_rate);
		#endif

		double* total_error = new double(0);
		const double* output = net.train(values, expected, *total_error);

		if (PRINT_OUTPUT)
			cout << "{ " << values[0] << ", " << values[1] << " } = " << output[0] << " | Error: " << *total_error << endl;

		// Cleanup
		delete[] values;
		delete total_error;
	}
	delete[] expected;
}

void trainer::train_handwritten_digits(network& net, int train_times, string mnist_filepath)
{

}
