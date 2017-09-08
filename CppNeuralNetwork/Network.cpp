#include "stdafx.h"
#include "Network.h"
#include "Functions.h"
#include <iostream> //TODO: REMOVE


// The network's layers
int* layers;

// ctor
Network::Network(int layerCount)
{
	if (layerCount < 1) throw "Layer count cannot be 0 or less!";
	layers = new int[layerCount];
}

// dctor
Network::~Network()
{
	layers = NULL;
}

// Train network and adjust weights to expectedOutput
void Network::Train(int inputValues[], int weights[], double expectedOutput)
{
	int size = sizeof(inputValues) / sizeof(inputValues[0]); // Length of inputValues (and eff. weights)
	double sum = 0; // sum of inputValues

	// Calculate the sum of all input values
	for (int i = 0; i < size; i++)
	{
		// Add to the sum but include neuron weight
		sum += inputValues[i] * weights[i];
	}

	// Squash the sum of input values
	double flattened = Squash(sum);

	std::cout << flattened;
}