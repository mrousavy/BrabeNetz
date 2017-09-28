#include "stdafx.h"
#include "Network.h"
#include <ctime>
#include "Functions.h"
using namespace std;

// TODO: REMOVE INCLUDES
#include "Extensions.h"

// ctor
network::network(initializer_list<int> initializer_list)
{
	srand(time(nullptr));

	if (initializer_list.size() < 3)
		throw "Initializer List can't contain less than 3 elements. E.g: { 2, 3, 4, 1 }: 2 Input, 3 Hidden, 4 Hidden, 1 Output";

	vector<int> inputVector; // clone initializer list to vector
	inputVector.insert(inputVector.end(), initializer_list.begin(), initializer_list.end());

	this->topology_ = network_topology::random(inputVector);
	init(this->topology_);
	fill_weights(this->topology_);
}

network::network(network_topology& topology)
{
	srand(time(nullptr));

	init(topology);
	fill_weights(topology);
}

void network::init(network_topology& topology)
{
	this->layers_count_ = topology.size; // Count of layers = input (1) + hidden + output (1)
	this->layers_ = new double*[this->layers_count_];
	this->neurons_count_ = new int[this->layers_count_];

	for (int i = 0; i < this->layers_count_; i++)
	{
		int layerSize = topology.layer_at(i).size; // Size of this layer (Neurons count)
		this->neurons_count_[i] = layerSize; // Set neuron count on this hidden layer
		this->layers_[i] = new double[layerSize];
	}
}

// dector
network::~network()
{
	// cleanup
	delete_weights();
	delete[] this->neurons_count_;
}

// Train network and adjust weights to expectedOutput
double network::train(double* inputValues, int length, double expectedOutput)
{
	int* outputLength = new int;
	double* outputLayer = feed(inputValues, length, *outputLength);

	vector<double> vec = extensions::to_vector<double>(outputLayer, *outputLength); // TODO: REMOVE TOVECTOR

	double sum = 0;
	for (int i = 0; i < *outputLength; i++) // Loop through each neuron in output layer
	{
		sum += squash(rectify(outputLayer[i])); // Squash and ReLU it (keep if positive, 0 if negative; uint)
	}

	// TODO: RETURN LAST ERROR
	return vec.at(0);
}

// Feed the network information and return the output
double* network::feed(double* inputValues, int length, int& outLength)
{
	double* values = inputValues; // Values of current layer
	int* valuesLength = new int(length); // Copy input length to variable
	for (int hiddenIndex = 1; hiddenIndex < this->layers_count_; hiddenIndex++) // Loop through each hidden layer
	{
		values = to_next_layer(values, *valuesLength, hiddenIndex, *valuesLength);
		vector<double> vec = extensions::to_vector<double>(values, *valuesLength); // TODO: REMOVE TOVECTOR
	}

	double sum = 0;
	for (int i = 0; i < *valuesLength; i++) // Loop through each neuron in output layer
	{
		sum += squash(rectify(values[i])); // Squash and ReLU it (keep if positive, 0 if negative; uint)
	}

	outLength = *valuesLength;
	return values;
}

// This function focuses on only one layer, so in theory we have 1 input layer, the layer we focus on, and 1 output
double* network::to_next_layer(double* inputValues, int inputLength, int layerIndex, int& outLength)
{
	vector<double> vec = extensions::to_vector<double>(inputValues, inputLength); // TODO: REMOVE TOVECTOR
	int nCount = this->neurons_count_[layerIndex]; // Count of neurons in the next layer (w/ layerIndex)
	double** weights = this->weights_[layerIndex - 1]; // ptr to weights of neurons in this layer
	double* biases = this->biases_[layerIndex]; // ptr to biases of neurons in the next layer
	double* layer = this->layers_[layerIndex];

	for (int n = 0; n < nCount; n++) // Loop through each neuron "n" on the next layer
	{
		layer[n] = 0; // Reset neuron's value

		for (int ii = 0; ii < inputLength; ii++) // Loop through each input value "ii"
		{
			layer[n] += inputValues[ii] * weights[ii][n]; // Add Value * Weight to that neuron
		}

		double result = layer[n] + biases[n];
		layer[n] = squash(result); // Squash result
	}

	outLength = nCount;
	return layer;
}

// TODO: Check if this works
void network::fill_weights(network_topology& topology)
{
	this->topology_ = topology;

	// layer weights has a reference on the heap
	if (this->weights_ != nullptr)
		delete_weights();

	int count = this->layers_count_ - 1; // Count of layers with connections
	this->weights_ = new double**[count]; // init first dimension; count of layers with connections

	int lcount = topology.size; // Count of layers
	this->biases_ = new double*[lcount];
	this->weights_ = new double**[lcount];
	for (int l = 0; l < lcount; l++) // Loop through each layer
	{
		layer& layer = topology.layer_at(l);
		int ncount = layer.size; // Count of neurons in this layer
		this->biases_[l] = new double[ncount];
		this->weights_[l] = new double*[ncount];
		for (int n = 0; n < ncount; n++) // Loop through each neuron in this layer
		{
			neuron& neuron = layer.neuron_at(n);

			this->biases_[l][n] = neuron.bias;
			int ccount = neuron.size; // Count of connection on this neuron
			this->weights_[l][n] = new double[ccount];
			for (int c = 0; c < neuron.size; c++) // Loop through each connection on this neuron
			{
				this->weights_[l][n][c] = neuron.connection_at(c).weight;
			}
		}
	}
}

void network::adjust(double expected, double actual)
{
	double error = get_error(expected, actual); // Error on output layer

}

void network::save(string path)
{
	// TODO: Serialize NetworkTopology and save it
}

void network::load(string path)
{
	// TODO: Deserialize NetworkTopology and load it
}

void network::delete_weights()
{
	for (int i = 0; i < this->layers_count_ - 1; i++) // Loop through each layer
	{
		int lneurons = this->neurons_count_[i];

		for (int n = 0; n < lneurons; n++) // Loop through each neuron in this layer
		{
			delete[] this->weights_[i][n]; // Delete all connections on this neuron
		}
		delete[] this->weights_[i]; // Delete all neurons on this layer
	}
	delete[] this->weights_; // Delete layer
}