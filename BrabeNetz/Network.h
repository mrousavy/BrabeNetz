#pragma once
#include "Functions.h"
#include "NetworkTopology.h"
#include <algorithm>
#include <vector>
using namespace std;

// Specifies the value each weight gets adjusted by on training
#define ADJUST_WEIGHTS_BY 0.002

class Network
{
public:
	////////////////
	//    ctor    //
	////////////////
	// initializerList: { 2, 3, 4, 1 }: 2 Input, 3 Hidden, 4 Hidden, 1 Output
	Network(initializer_list<int> initializerList);
	// initializerList: { 2, 3, 4, 1 }: 2 Input, 3 Hidden, 4 Hidden, 1 Output
	Network(initializer_list<int> initializerList, NetworkTopology& topology);
	~Network();

	////////////////
	// functions  //
	////////////////
	// Feed the network information and train it to adjust to the expected output (returns accuracy/error)
	double Train(double* inputValues, int length, double expectedOutput);
	// Feed the network information and return the output
	double Feed(double* inputValues, int length);
	// Save the network's state to disk by serializing weights
	void Save(string path);
	// Load the network's state from disk by deserializing and loading weights
	void Load(string path);

private:
	////////////////
	// properties //
	////////////////
	// Count of Neurons in Input Layer
	int inputNeuronsCount;
	// Count of Hidden Layers
	int hiddenLayersCount;
	// Count of Neurons in Hidden Layers (LTR in Topology)
	int* hiddenNeuronsCount;
	// Count of Neurons in Output Layer
	int outputNeuronsCount;
	// Weight of each neuron's connection, 3D Array: [layer][neuron][connection]
	double*** weights;
	// The network topology, only for logic representation and weights initialization
	NetworkTopology* topology;


	////////////////
	// functions  //
	////////////////
	// Put inputValues into layer at given layerIndex with squashing, etc and return layer's values
	double* ToNextLayer(double* inputValues, int inputLength, int layerIndex, int& outLength);
	// Fill neuron weights with random values
	void RandomizeWeights();
	// Fill neuron weights with given values
	void FillWeights(NetworkTopology& topology);
	// Init Network
	void Init(initializer_list<int>* initializerList);
	// Delete weights array
	void DeleteWeights();
};

