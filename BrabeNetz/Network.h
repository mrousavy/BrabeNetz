#pragma once
#include "Functions.h"
#include "NetworkTopology.h"
#include <algorithm>
#include <vector>
#include <time.h>
using namespace std;

// Specifies the value each weight gets adjusted by on training
#define ADJUST_WEIGHTS_BY 0.002
// Maximum delta of actual and expected values until stop training
#define MAX_DELTA 0.01

class Network
{
public:
	////////////////
	//    ctor    //
	////////////////
	// initializerList: { 2, 3, 4, 1 }: 2 Input, 3 Hidden, 4 Hidden, 1 Output
	Network(initializer_list<int> initializerList);
	// initializerList: { 2, 3, 4, 1 }: 2 Input, 3 Hidden, 4 Hidden, 1 Output
	Network(NetworkTopology& topology);
	~Network();

	////////////////
	// functions  //
	////////////////
	// Feed the network information and train it to adjust to the expected output (returns output error)
	double Train(double* inputValues, int length, double expectedOutput);
	// Feed the network information and return the output layer
	double* Feed(double* inputValues, int length, int& outLength);
	// Save the network's state to disk by serializing weights
	void Save(string path);
	// Load the network's state from disk by deserializing and loading weights
	void Load(string path);

private:
	////////////////
	// properties //
	////////////////
	// Count of Layers in this network
	int layersCount;
	// Count of Neurons in Layers (Left to right in Topology)
	int* neuronsCount;
	// Actual layers that contain nodes with their values
	double** layers;
	// Each neuron's bias
	double** biases;
	// Each neuron's error values
	double** errors;
	// Weight of each neuron's connection, 3D Array: [layer][neuron][connection]
	double*** weights;
	// The network topology, only for logic representation and weights initialization
	NetworkTopology topology;


	////////////////
	// functions  //
	////////////////
	// Init Network
	void Init(NetworkTopology& topology);
	// Put inputValues into layer at given layerIndex with squashing, etc and return layer's values
	double* ToNextLayer(double* inputValues, int inputLength, int layerIndex, int& outLength);
	// Adjust Network's weights and Biases
	void Adjust(double expected, double actual);
	// Fill neuron weights with given values
	void FillWeights(NetworkTopology& topology);
	// Delete weights array
	void DeleteWeights();
};

