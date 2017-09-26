// __ConsoleEntry.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Functions.h"
#include "Network.h"
#include "Trainer.h"

using namespace std;


int main()
{
	// boot up neuronal network
	Network* net = new Network({ 2, 3, 1 });
	// boot up neuronal network trainer
	Trainer* trainer = new Trainer(net);
	trainer->TrainXor();


	// cleanup
	delete net;
	delete trainer;

	// Exit on user input
	string _ = "";
	cin >> _;
}

