#include "stdafx.h"
#include "Network.h"
#include "Functions.h"
#include <iostream> //TODO: REMOVE
#include <vector>
#include <algorithm>
using namespace std;

// Specifying the amount of neurons to get combined for the next layer
#define NEURON_LAYER_COMBINE 2
// Specifying the amount of hidden neuron layers to use (layers between input and output layer)
#define NEURON_LAYER_COUNT 2




// ctor
Network::Network(initializer_list<int> initializerList)
{
	if (initializerList.size() < 3)
		throw "Initializer List can't contain less than 3 elements. E.g: { 2, 3, 4, 1 }: 2 Input, 3 Hidden, 4 Hidden, 1 Output";

	vector<int> inputVector; // clone initializer list to vector
	inputVector.insert(inputVector.end(), initializerList.begin(), initializerList.end());

	this->inputNeuronsCount = inputVector[0]; // First element in vector -> input
	this->outputNeuronsCount = inputVector.back(); // Last element in vector -> output
	int hiddenCount = inputVector.size() - 2; // Count of hidden layers
	this->hiddenNeuronsCount = new int[hiddenCount]; // elements except first and last = hidden layers
	this->layers = new int*[hiddenCount]; // Init all hidden layers (between input & output)

	int hiddenIndex = 1; // index on input vector
	for (int i = 0; hiddenIndex <= hiddenCount; i++) // Loop from [1] to [last-1] (all hidden layers)
	{
		int layerSize = inputVector[hiddenIndex];
		this->hiddenNeuronsCount[i] = layerSize;
		this->layers[i] = new int[layerSize];
		hiddenIndex++;
	}
}

// dector
Network::~Network()
{
	delete this->layers;
}

// Train network and adjust weights to expectedOutput
void Network::Train(vector<double>* inputValues, vector<double>* weights, double expectedOutput)
{
	double output = Feed(inputValues, weights);

	if (output == expectedOutput)
		return; // it's trained good enough

	//TODO: Adjust network
}

// Feed the network information and return the output
double Network::Feed(vector<double>* inputValues, vector<double>* weights)
{
	int size = inputValues->size(); // Length of inputValues (and eff. weights)
	int lindex = size - 1; // Last index of inputValues (and eff. weights)
	vector<double>* sums = new vector<double>;

	// Calculate the sum of all input values
	for (int current = 0; current < size; current++)
	{
		double sum = 0; // sum of inputValues

        // Loop NEURON_LAYER_COMBINE times (default: 2)
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

	double sum = Sum(sums); // sum of all individual neuron sums
	delete sums; // Cleanup
	return sum; // Return "result" (last output node)
}

void Network::Save(string path)
{
	// TODO
}

void Network::Load(string path)
{
	// TODO
}