#include "stdafx.h"
#include "Network.h"
using namespace std;

// TODO: REMOVE INCLUDES
#include "Extensions.h"

// ctor
Network::Network(initializer_list<int> initializerList)
{
	srand(time(NULL));

	if (initializerList.size() < 3)
		throw "Initializer List can't contain less than 3 elements. E.g: { 2, 3, 4, 1 }: 2 Input, 3 Hidden, 4 Hidden, 1 Output";

	vector<int> inputVector; // clone initializer list to vector
	inputVector.insert(inputVector.end(), initializerList.begin(), initializerList.end());

	this->topology = NetworkTopology::Random(inputVector);
	Init(this->topology);
	FillWeights(this->topology);
}

Network::Network(NetworkTopology& topology)
{
	srand(time(NULL));

	Init(topology);
	FillWeights(topology);
}

void Network::Init(NetworkTopology& topology)
{
	this->layersCount = topology.Size; // Count of layers = input (1) + hidden + output (1)
	this->layers = new double*[this->layersCount];
	this->neuronsCount = new int[this->layersCount];

	for (int i = 0; i < this->layersCount; i++)
	{
		int layerSize = topology.LayerAt(i).Size; // Size of this layer (Neurons count)
		this->neuronsCount[i] = layerSize; // Set neuron count on this hidden layer
		this->layers[i] = new double[layerSize];
	}
}

// dector
Network::~Network()
{
	// cleanup
	DeleteWeights();
	delete[] this->neuronsCount;
}

// Train network and adjust weights to expectedOutput
double Network::Train(double* inputValues, int length, double expectedOutput)
{
	double output = Feed(inputValues, length);
	return output; // TODO: REMOVE

	double delta = abs(output - expectedOutput);

	if (delta > MAX_DELTA)
		Adjust(expectedOutput, output);

	return delta;
}

// Feed the network information and return the output
double Network::Feed(double* inputValues, int length)
{
	double* values = inputValues; // Values of current layer
	int* valuesLength = new int(length); // Copy input length to variable
	for (int hiddenIndex = 1; hiddenIndex < this->layersCount; hiddenIndex++) // Loop through each hidden layer
	{
		values = ToNextLayer(values, *valuesLength, hiddenIndex, *valuesLength);
		vector<double> vec = Extensions::ToVector<double>(values, *valuesLength);
	}

	double sum = 0;
	for (int i = 0; i < *valuesLength; i++) // Loop through each neuron in output layer
	{
		double value = Rectify(values[i]); // ReLU it (keep if positive, 0 if negative; uint)
		sum += Squash(value); // Squash the result
	}


	return sum;
}

// This function focuses on only one layer, so in theory we have 1 input layer, the layer we focus on, and 1 output
double* Network::ToNextLayer(double* inputValues, int inputLength, int layerIndex, int& outLength)
{
	int nCount = this->neuronsCount[layerIndex]; // Count of neurons in the next layer (w/ layerIndex)
	double** weights = this->weights[layerIndex - 1]; // ptr to weights of neurons in this layer
	double* biases = this->biases[layerIndex]; // ptr to biases of neurons in the next layer
	double* layer = this->layers[layerIndex];

	for (int n = 0; n < nCount; n++) // Loop through each neuron "n" on the next layer
	{
		layer[n] = 0; // Reset neuron's value

		for (int ii = 0; ii < inputLength; ii++) // Loop through each input value "ii"
		{
			layer[n] += inputValues[ii] * weights[ii][n]; // Add Value * Weight to that neuron
		}

		double result = layer[n] + biases[n];
		layer[n] = Squash(result); // Squash result
	}

	outLength = nCount;
	return layer;
}

// TODO: Check if this works
void Network::FillWeights(NetworkTopology& topology)
{
	this->topology = topology;

	// layer weights has a reference on the heap
	if (this->weights != nullptr)
		DeleteWeights();

	int count = this->layersCount - 1; // Count of layers with connections
	this->weights = new double**[count]; // init first dimension; count of layers with connections

	int lcount = topology.Size; // Count of layers
	this->biases = new double*[lcount];
	this->weights = new double**[lcount];
	for (int l = 0; l < lcount; l++) // Loop through each layer
	{
		Layer& layer = topology.LayerAt(l);
		int ncount = layer.Size; // Count of neurons in this layer
		this->biases[l] = new double[ncount];
		this->weights[l] = new double*[ncount];
		for (int n = 0; n < ncount; n++) // Loop through each neuron in this layer
		{
			Neuron& neuron = layer.NeuronAt(n);

			this->biases[l][n] = neuron.Bias;
			int ccount = neuron.Size; // Count of connection on this neuron
			this->weights[l][n] = new double[ccount];
			for (int c = 0; c < neuron.Size; c++) // Loop through each connection on this neuron
			{
				this->weights[l][n][c] = neuron.ConnectionAt(c).Weight;
			}
		}
	}
}

void Network::Adjust(double expected, double actual)
{
	double error = GetError(expected, actual); // Error on output layer

}

void Network::Save(string path)
{
	// TODO: Serialize NetworkTopology and save it
}

void Network::Load(string path)
{
	// TODO: Deserialize NetworkTopology and load it
}

void Network::DeleteWeights()
{
	for (int i = 0; i < this->layersCount - 1; i++) // Loop through each layer
	{
		int lneurons = this->neuronsCount[i];

		for (int n = 0; n < lneurons; n++) // Loop through each neuron in this layer
		{
			delete[] this->weights[i][n]; // Delete all connections on this neuron
		}
		delete[] this->weights[i]; // Delete all neurons on this layer
	}
	delete[] this->weights; // Delete layer
}