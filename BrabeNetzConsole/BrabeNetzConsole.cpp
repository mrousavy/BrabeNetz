// BrabeNetzConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <omp.h>
#include "Console.h"
#include "Trainer.h"
#include "../BrabeNetz/Network.h"
using namespace std;

// Load saved network state from disk instead of randomizing a new one each start
#define LOAD_STATE true
// Amount of times to train the network
#define TRAIN_TIMES_EACH 4000

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
	else
		printf("Not using NVIDIA CUDA.\n");
}

int main()
{
	try {
		console::set_title("BrabeNetz - Neural Network");

		srand(time(nullptr));

		print_info();

		printf("\nLoading state.nn/randomizing new network..\n");

		// boot up/load neuronal network
		const auto boot_start = chrono::high_resolution_clock::now();
		network* net;
		if (LOAD_STATE && ifstream("state.nn", fstream::in | fstream::binary)) // Load if file exists
			net = new network("state.nn");
		else // Else create random network
			net = new network({ 784,500,100,10 }); //TODO: {784,16,16,10} ?
		const auto boot_finish = chrono::high_resolution_clock::now();

		printf("Starting network training for %i times..\n", TRAIN_TIMES_EACH);

		// Train neural network with trainer
		//const auto train_microsecs = trainer::train_xor(*net, TRAIN_TIMES_EACH);
		const auto train_microsecs = trainer::train_handwritten_digits(*net, "train-images.idx3-ubyte", "train-labels.idx1-ubyte");
		const double train_time = train_microsecs / 1000.0;

		printf("Training done!\n\n");

		const auto boot_time = std::chrono::duration_cast<chrono::microseconds>(boot_finish - boot_start).count() / 1000.0;

		printf("Bootup time: %.2fms | Train time: %.2fms | Total: %.2fms\n", boot_time, train_time, boot_time + train_time);

		net->save();
		printf("Saved state to state.nn file.\n\n");

		delete net;
	}
	catch (exception exc) {
		cout << exc.what() << endl;
	}
	catch (string error) {
		cout << error << endl;
	}

	// Exit on user input
	printf("Press any key to exit..");
	getchar();
}
