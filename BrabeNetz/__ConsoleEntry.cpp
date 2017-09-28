// __ConsoleEntry.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <string>
#include "Network.h"
#include "Trainer.h"
#include <chrono>

using namespace std;


int main()
{
	// boot up neuronal network
	const auto boot_start = std::chrono::high_resolution_clock::now();
	network* net = new network({ 2, 3, 1 });
	const auto boot_finish = std::chrono::high_resolution_clock::now();

	// boot up neuronal network trainer
	trainer* coach = new trainer(net);

	// Train neural network with trainer
	const auto train_start = std::chrono::high_resolution_clock::now();
	coach->train_xor();
	const auto train_finish = std::chrono::high_resolution_clock::now();

	// cleanup
	delete net;
	delete coach;

	const auto boot_time = std::chrono::duration_cast<std::chrono::milliseconds>(boot_finish - boot_start).count();
	const auto train_time = std::chrono::duration_cast<std::chrono::milliseconds>(train_finish - train_start).count();

	cout << "Bootup time: " << boot_time 
		<< "ms | Train time: " << train_time 
		<< "ms | Total: " << boot_time + train_time 
		<< "ms" << endl;

	// Exit on user input
	string _ = "";
	cin >> _;
}