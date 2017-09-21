#pragma once
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
	// properties //
	////////////////
	// Count of Neurons in Input Layer
	int inputNeuronsCount;
	// Count of Neurons in Hidden Layers (LTR in Topology)
	int* hiddenNeuronsCount;
	// Count of Neurons in Output Layer
	int outputNeuronsCount;
	// Actual Hidden layers
	int** layers;

	////////////////
	// functions  //
	////////////////
	// Feed the network information and train it to adjust to the expected output
	void Train(vector<double>* inputValues, vector<double>* weights, double expectedOutput);
	// Feed the network information and return the output
	double Feed(vector<double>* inputValues, vector<double>* weights);
	// Save the network's state to disk by serializing weights
	void Save(string path);
	// Load the network's state from disk by deserializing and loading weights
	void Load(string path);
};

