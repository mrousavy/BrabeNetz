// __ConsoleEntry.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <string>
#include "Functions.h"
#include "Network.h"
#include "Trainer.h"
#include <chrono>

using namespace std;


int main()
{
	// boot up neuronal network
	auto bootStart = std::chrono::high_resolution_clock::now();
	Network* net = new Network({ 2, 3, 1 });
	auto bootFinish = std::chrono::high_resolution_clock::now();

	// boot up neuronal network trainer
	Trainer* trainer = new Trainer(net);

	// Train neural network with trainer
	auto trainStart = std::chrono::high_resolution_clock::now();
	trainer->TrainXor();
	auto trainFinish = std::chrono::high_resolution_clock::now();

	// cleanup
	delete net;
	delete trainer;

	auto bootTime = std::chrono::duration_cast<std::chrono::milliseconds>(bootFinish - bootStart).count();
	auto trainTime = std::chrono::duration_cast<std::chrono::milliseconds>(trainFinish - trainStart).count();

	cout << "Bootup time: " << bootTime 
		<< "ms | Train time: " << trainTime 
		<< "ms | Total: " << bootTime + trainTime 
		<< "ms" << endl;

	// Exit on user input
	string _ = "";
	cin >> _;
}