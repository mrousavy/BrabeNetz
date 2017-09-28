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
	const auto boot_start = chrono::high_resolution_clock::now();
	network net{2,3,1};
	const auto boot_finish = chrono::high_resolution_clock::now();

	// Train neural network with trainer
	const auto train_start = chrono::high_resolution_clock::now();
	trainer::train_xor(net);
	const auto train_finish = chrono::high_resolution_clock::now();


	const auto boot_time = std::chrono::duration_cast<chrono::milliseconds>(boot_finish - boot_start).count();
	const auto train_time = std::chrono::duration_cast<chrono::milliseconds>(train_finish - train_start).count();

	cout << "Bootup time: " << boot_time
		<< "ms | Train time: " << train_time
		<< "ms | Total: " << boot_time + train_time
		<< "ms" << endl;

	net.save();

	// Exit on user input
	string _ = "";
	cin >> _;
}
