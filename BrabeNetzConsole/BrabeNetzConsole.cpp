// BrabeNetzConsole.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include "../BrabeNetz/Network.h"
#include "../BrabeNetz/Trainer.h"
using namespace std;

// Load saved network state from disk instead of randomizing a new one each start
#define LOAD_STATE false
// Amount of times to train the network
#define TRAIN_TIMES_EACH 1000

void print_info()
{
	int available_threads = 0;
	#pragma omp parallel
	{
		available_threads++;
	}
	cout << "Available OpenMP Threads: " << available_threads << endl;

	const bool use_cuda = false;
	const int core_count = 0;
	if (use_cuda)
		cout << "Using NVIDIA CUDA with " << core_count << " cores" << endl;
	else
		cout << "Not using NVIDIA CUDA" << endl;
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

	const auto boot_time = std::chrono::duration_cast<chrono::milliseconds>(boot_finish - boot_start).count();
	const auto train_time = std::chrono::duration_cast<chrono::milliseconds>(train_finish - train_start).count();

	cout << "Bootup time: " << boot_time
		<< "ms | Train time: " << train_time
		<< "ms | Total: " << boot_time + train_time
		<< "ms" << endl;

	net->save();

	delete net;

	// Exit on user input
	getchar();
}
