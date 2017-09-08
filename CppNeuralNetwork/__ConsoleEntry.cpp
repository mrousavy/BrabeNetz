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
		double x = Squash(weight);
		cout << "Squashing " << weight << " = " << x << endl;
	}

	// boot up neuronal network
	Network* net = new Network(50);
	// boot up neuronal network trainer
	Trainer* trainer = new Trainer(net);
	trainer->TrainXor();

	// cleanup
	net = NULL;
	trainer = NULL;

	string _ = "";
	cin >> _;
}

