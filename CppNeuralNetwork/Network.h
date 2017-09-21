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
	vector<int>* layers;
	int inputNeuronsSize;
	int* layerNeuronsSize;
	int outputNeuronsSize;

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

