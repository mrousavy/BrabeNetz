#include "stdafx.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <omp.h>
#include "Console.h"
#include "Trainer.h"
using namespace std;

// Load saved network state from disk instead of randomizing a new one each start
#define LOAD_STATE true
// Amount of times to train the network
#define TRAIN_TIMES_EACH 10000
// Train Image recognition? MNIST
//#define TRAIN_IMAGE
// Train XOR Logic gate?
#define TRAIN_XOR

void print_info()
{
#pragma omp parallel
	{
		if (omp_in_parallel())
		{
#pragma omp single
			printf("Running in parallel with %i OpenMP threads.\n", omp_get_num_threads());
		}
		else
		{
#pragma omp single
			printf("Running in serial, no multithreading is used.\n");
		}
	}

	const bool use_cuda = false;
	const int core_count = 0;
	if (use_cuda)
		printf("Using NVIDIA CUDA with %i cores\n", core_count);
	printf("Not using NVIDIA CUDA.\n");
}

int main()
{
	try
	{
		console::set_title("BrabeNetz - Neural Network");

		srand(static_cast<unsigned>(time(nullptr)));

		print_info();

		printf("\nLoading state.nn/randomizing new network..\n");

		properties properties("state.nn");

		// boot up/load neuronal network
		const auto boot_start = chrono::high_resolution_clock::now();
#ifdef TRAIN_IMAGE
#ifdef LOAD_STATE
			network net(properties);
#else
			network net({ 784, 16, 16, 10 }, properties);
#endif
#endif
#ifdef TRAIN_XOR
#ifdef LOAD_STATE
		brabenetz xor_net(properties);
#else
			brabenetz xor_net({ 2, 3, 1 }, properties);
#endif
#endif
		const auto boot_finish = chrono::high_resolution_clock::now();


		// Train neural network with trainer
		long long train_microsecs{0};
#ifdef TRAIN_IMAGE
		train_microsecs += trainer::train_handwritten_digits(net, "train-images-idx3-ubyte",
															 "train-labels-idx1-ubyte");
#endif
#ifdef TRAIN_XOR
		train_microsecs += trainer::train_xor(xor_net, TRAIN_TIMES_EACH * 4);
#endif
		const double train_time = train_microsecs / 1000.0;

		printf("Training done!\n\n");

		const auto boot_time = std::chrono::duration_cast<chrono::microseconds>(boot_finish - boot_start).count() /
			1000.0;

		printf("Bootup time: %.2fms | Train time: %.2fms | Total: %.2fms\n", boot_time, train_time,
		       boot_time + train_time);

#ifdef TRAIN_IMAGE
		net.save();
#endif
#ifdef TRAIN_XOR
		xor_net.save();
#endif
		printf("Saved state to state.nn file.\n\n");
	}
	catch (runtime_error& error)
	{
		cout << error.what() << endl;
	}
	catch (string& msg)
	{
		cout << msg << endl;
	}

	// Exit on user input
	printf("Press any key to exit..");
	getchar();
}
