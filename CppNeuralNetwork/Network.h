#pragma once
#include "Functions.h"
#include <iostream> //TODO: REMOVE
#include <algorithm>
#include <vector>
using namespace std;

class Network
{
public:
	////////////////
	//    ctor    //
	////////////////
	// initializerList: { 2, 3, 4, 1 }: 2 Input, 3 Hidden, 4 Hidden, 1 Output
	Network(initializer_list<int> initializerList);
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
	// Actual Hidden layers
	double** layers;
	// Weight of each neuron's connection, 3D Array: [layer][neuron][connection]
	double*** connectionWeights;
	// Weight of each neuron in the Output layer
	double* outputWeights;


	////////////////
	// functions  //
	////////////////
	// Put inputValues into layer at given layerIndex with squashing, etc and return layer's values
	double* ToNextLayer(double* inputValues, int inputLength, int layerIndex, int& outLength);
	// Fill neuron weights with random values
	void RandomizeWeights();
};

