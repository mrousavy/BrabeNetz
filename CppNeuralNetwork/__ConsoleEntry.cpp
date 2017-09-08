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
	for (double weight = -64; weight < 64; weight++)
	{
		// Test squashing
		double x = Squash(weight);
		cout << "Squashing " << weight << " = " << x << endl;
	}
	cout << endl << endl;

	// boot up neuronal network
	Network* net = new Network(50);
	// boot up neuronal network trainer
	Trainer* trainer = new Trainer(net);
	trainer->TrainXor();

	// cleanup
	net = NULL;
	trainer = NULL;

	// Exit on user input
	string _ = "";
	cin >> _;
}

