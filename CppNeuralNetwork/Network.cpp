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
	this->layerWeights = new double*[hiddenLayersCount]; // Init the weights of all hidden layers (between in- & output)

	int hiddenIndex = 1; // index on input vector
	for (int i = 0; hiddenIndex <= hiddenLayersCount; i++) // Loop from [1] to [last-1] (all hidden layers)
	{
		int layerSize = inputVector[hiddenIndex]; // Layer size of this layer (Containing neurons)
		this->hiddenNeuronsCount[i] = layerSize; // Set neuron count on this hidden layer
		this->layers[i] = new double[layerSize]; // Create layer with neuron size in hidden-layers array
		this->layerWeights[i] = new double[layerSize]; // Init the layer weights for this layer
		for (int nI = 0; nI < layerSize; nI++) // loop through each neuron (nI = neuron index)
		{
			// Set all layer weights on this layer to a random number between 0 or 1 (2 digits precision)
			this->layerWeights[i][nI] = double(rand() % 100) / 100;
		}

		hiddenIndex++;
	}
}

// dector
Network::~Network()
{
	delete this->hiddenNeuronsCount;
	delete this->layers;
	delete this->layerWeights;
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

	vector<double>* values = inputValues; // Values of current layer
	// Go through each hidden layer
	for (int hiddenIndex = 0; hiddenIndex < this->hiddenLayersCount; hiddenIndex++)
	{
		values = ToNextLayer(values, hiddenIndex);
	}

	// `values` are last layer's values by now -> to output layer
	// TODO ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

	double sum = Sum(sums); // sum of all individual neuron sums
	delete sums; // Cleanup
	delete values;
	return sum; // Return "result" (last output node)
}

// This function focuses on only one layer, so in theory we have 1 input layer, the layer we focus on, and 1 output
vector<double>* Network::ToNextLayer(vector<double>* inputValues, int layerIndex)
{
	int iSize = inputValues->size(); // Input values count/size
	int nCount = this->hiddenNeuronsCount[layerIndex]; // Count of neurons in the given layer (w/ layerIndex)
	double* layer = this->layers[layerIndex]; // ptr to neurons in this layer
	double* weights = this->layerWeights[layerIndex]; // ptr to weights of neurons in this layer
	vector<double>* output = new vector<double>();

	// Loop through each neuron on the given layer
	for (int li = 0; li < nCount; li++) // li = layer index
	{
		layer[li] = 0; // Reset layer's neuron at index li

		// Loop through each value in the inputs (every input broadcasts to all neurons in this layer)
		for (int ii = 0; ii < iSize; ii++) // ii = input index
		{
			layer[li] += inputValues->at(ii) * weights[li]; // Add Value * Weight to that neuron
		}

		double neuron = layer[li]; // The current neuron's value
		neuron = Squash(neuron);
		output->push_back(neuron); // Add value to output layer
	}

	return output;
}


void Network::Save(string path)
{
	// TODO
}

void Network::Load(string path)
{
	// TODO
}