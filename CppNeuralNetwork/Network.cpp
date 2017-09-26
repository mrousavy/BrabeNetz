#include "stdafx.h"
#include "Network.h"
using namespace std;


// ctor
Network::Network(initializer_list<int> initializerList)
{
	if (initializerList.size() < 3)
		throw "Initializer List can't contain less than 3 elements. E.g: { 2, 3, 4, 1 }: 2 Input, 3 Hidden, 4 Hidden, 1 Output";

	vector<int> inputVector; // clone initializer list to vector
	inputVector.insert(inputVector.end(), initializerList.begin(), initializerList.end());

	this->inputNeuronsCount = inputVector[0]; // First element in vector -> input
	this->outputNeuronsCount = inputVector.back(); // Last element in vector -> output
	this->hiddenLayersCount = inputVector.size() - 2; // Count of hidden layers = total items in vector minus end and start
	this->hiddenNeuronsCount = new int[hiddenLayersCount]; // elements except first and last = hidden layers
	this->layers = new double*[hiddenLayersCount]; // Init all hidden layers (between input & output)

	int hiddenIndex = 1; // index on input vector
	for (int i = 0; hiddenIndex <= hiddenLayersCount; i++) // Loop from [1] to [last-1] (all hidden layers)
	{
		int layerSize = inputVector[hiddenIndex]; // Layer size of this layer (Containing neurons)
		this->hiddenNeuronsCount[i] = layerSize; // Set neuron count on this hidden layer
		this->layers[i] = new double[layerSize]; // Create layer with neuron size in hidden-layers array

		hiddenIndex++;
	}
	RandomizeWeights(); // Calculate weights
}

// dector
Network::~Network()
{
	// cleanup
	delete this->hiddenNeuronsCount;
	delete this->layers;
	delete this->connectionWeights;
}

// Train network and adjust weights to expectedOutput
void Network::Train(double* inputValues, int length, double expectedOutput)
{
	double output = Feed(inputValues, length);

	if (output == expectedOutput)
		return; // it's trained good enough

	//TODO: Adjust network
}

// Feed the network information and return the output
double Network::Feed(double* inputValues, int length)
{
	int lindex = length - 1; // Last index of inputValues (and eff. weights)

	double* values = inputValues; // Values of current layer
	int* valuesLength = &length;
	// Go through each hidden layer
	for (int hiddenIndex = 0; hiddenIndex < this->hiddenLayersCount; hiddenIndex++)
	{
		double* addr = values; // Cache temp variable
		values = ToNextLayer(values, *valuesLength, hiddenIndex, *valuesLength);

		if (&addr != &inputValues) // Don't delete parameter
			delete addr; // Delete the old pointer
	}

	// TODO: OUTPUT

	// Cleanup

	return 0;
}

// This function focuses on only one layer, so in theory we have 1 input layer, the layer we focus on, and 1 output
double* Network::ToNextLayer(double* inputValues, int inputLength, int layerIndex, int& outLength)
{
	int nCount = this->hiddenNeuronsCount[layerIndex]; // Count of neurons in the given layer (w/ layerIndex)
	double* layer = this->layers[layerIndex]; // ptr to neurons in this layer
	double** weights = this->connectionWeights[layerIndex]; // ptr to weights of neurons in this layer
	double* output = new double[nCount];

	// TODO: FEED WITH correct weights

	// Loop through each neuron on the given layer
	for (int n = 0; n < nCount; n++) // n = neuron
	{
		layer[n] = 0; // Reset layer's neuron at index n

		// Loop through each value in the inputs (every input broadcasts to all neurons in this layer)
		for (int ii = 0; ii < inputLength; ii++) // ii = input index
		{
			layer[n] += inputValues[ii] * weights[layerIndex][n]; // Add Value * Weight to that neuron
		}

		double neuron = layer[n]; // The current neuron's value
		neuron = Squash(neuron);
		output[n] = neuron; // Add value to output layer
	}

	// TODO: is that safe to do?
	delete layer;
	delete weights;

	outLength = nCount;
	return output;
}

void Network::RandomizeWeights()
{
	// layer weights has a reference on the heap
	if (this->connectionWeights != nullptr)
	{
		// delete the reference
		delete this->connectionWeights;
	}

	int count = this->hiddenLayersCount + 1; // Count of layers with connections
	this->connectionWeights = new double**[hiddenLayersCount];

	// Fill input layer weights
	this->connectionWeights[0] = new double*[this->inputNeuronsCount]; // [0] is input layer
	int nextLayerNeuronCount = this->hiddenNeuronsCount[0]; // Count of neurons in first hidden layer
	for (int i = 0; i < this->inputNeuronsCount; i++) // Loop through each neuron in input layer
	{
		this->connectionWeights[0][i] = new double[nextLayerNeuronCount];

		for (int ni = 0; ni < nextLayerNeuronCount; ni++) // Loop through each connection on that neuron
		{
			// Set all layer weights on this layer to a random number between 0 or 1 (2 digits precision)
			this->connectionWeights[0][i][ni] = double(rand() % 100) / 100;
		}
	}


	// Fill hidden layers weights
	for (int i = 0; i < count; i++)
	{
		int neuronsCount = this->hiddenNeuronsCount[i]; // Count of neurons on that layer
		// TODO: OUT OF BOUNDS?
		int nextNeuronsCount = this->hiddenNeuronsCount[i + 1]; // Count of neurons in next layer
		for (int ni = 0; ni < neuronsCount; ni++)
		{
			for (int nni = 0; nni < nextNeuronsCount; nni++)
			{
				this->connectionWeights[i + 1][ni][nni] = double(rand() % 100) / 100;
			}
		}
	}
}


void Network::Save(string path)
{
	// TODO
}

void Network::Load(string path)
{
	// TODO
}