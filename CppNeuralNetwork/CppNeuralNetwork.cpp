// CppNeuralNetwork.cpp : Defines the entry point for the console application.
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
	float weight = 63;
	float x = Squash(weight);
	cout << weight << "=" << x;

	// boot up neuronal network
	Network* net = new Network(50);
	// boot up neuronal network trainer
	Trainer* trainer = new Trainer(net);



	// cleanup
	net = NULL;
	trainer = NULL;
}

