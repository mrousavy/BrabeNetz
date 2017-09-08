#include "stdafx.h"
#include "Network.h"
#include "Functions.h"
#include <iostream> //TODO: REMOVE
#include <vector>
#include <algorithm>
using namespace std;

// Specifying the amount of neurons to get combined for the next layer
#define NEURON_LAYER_COMBINE 2


void print(double elem)
{
	cout << elem << endl;
}

// ctor
Network::Network()
{
	this->layers = new vector<int>();
}

// dctor
Network::~Network()
{
	this->layers = NULL;
}

// Train network and adjust weights to expectedOutput
void Network::Train(vector<double>* inputValues, vector<double>* weights, double expectedOutput)
{
	int size = inputValues->size(); // Length of inputValues (and eff. weights)
	int lindex = size - 1; // Last index of inputValues (and eff. weights)
	double sum;
	vector<double>* sums = new vector<double>;

	// Calculate the sum of all input values
	for (int current = 0; current < size; current++)
	{
		sum = 0; // sum of inputValues

		// Loop twice
		for (int i = 0; i < NEURON_LAYER_COMBINE; i++)
		{
			int next = current + i; // next layer index to add to (can be current aswell)
			int index = next == size // check for out of bounds
				? 0 // current is last element, go back to first
				: next; // use current/next element (current+1 | current+0)

			// Add to the sum and include neuron weight
			sum += inputValues->at(index) * weights->at(index);
		}

		// Squash the sum of input values
		double flattened = Squash(sum);

		sums->push_back(flattened); // add to final layer sum
	}

	for_each(sums->begin(), sums->end(), print);
}