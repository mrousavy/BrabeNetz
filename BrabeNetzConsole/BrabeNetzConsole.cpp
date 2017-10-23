// BrabeNetzConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <omp.h>
#include "Trainer.h"
#include "../BrabeNetz/Network.h"
using namespace std;

// Load saved network state from disk instead of randomizing a new one each start
#define LOAD_STATE false
// Amount of times to train the network
#define TRAIN_TIMES_EACH 1000

void print_info()
{
	#pragma omp parallel
	{
		if (omp_in_parallel())
		{
			#pragma omp single
			printf("Running in parallel with %i OpenMP threads.\n", omp_get_num_threads());
		} else
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
	srand(time(nullptr));

	print_info();

	// boot up/load neuronal network
	const auto boot_start = chrono::high_resolution_clock::now();
	network* net;
	if (LOAD_STATE && ifstream("state.nn", fstream::in | fstream::binary)) // Load if file exists
		net = new network("state.nn");
	else // Else create random network
		net = new network({ 2,3,1 });
	const auto boot_finish = chrono::high_resolution_clock::now();

	// Train neural network with trainer
	const auto train_start = chrono::high_resolution_clock::now();
	trainer::train_xor(*net, TRAIN_TIMES_EACH);
	//trainer::train_handwritten_digits(*net, TRAIN_TIMES_EACH, "train-images.idx3-ubyte", "train-labels.idx1-ubyte");
	const auto train_finish = chrono::high_resolution_clock::now();

	const auto boot_time = std::chrono::duration_cast<chrono::microseconds>(boot_finish - boot_start).count() / 1000.0;
	const auto train_time = std::chrono::duration_cast<chrono::microseconds>(train_finish - train_start).count() / 1000.0;

	printf("Bootup time: %.2fms | Train time: %.2fms | Total: %.2fms", boot_time, train_time, boot_time + train_time);

	net->save();

	delete net;

	// Exit on user input
	getchar();
}
