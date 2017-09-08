#pragma once
#include <vector>
using namespace std;

class Network
{
public:
	////////////////
	//    ctor    //
	////////////////
	Network();
	~Network();

	////////////////
	// properties //
	////////////////
	vector<int>* layers;

	////////////////
	// functions  //
	////////////////
	// Feed the network information and train it to adjust to the expected output
	void Train(vector<double>* inputValues, vector<double>* weights, double expectedOutput);
	// Feed the network information and return the output
	double Feed(vector<double>* inputValues, vector<double>* weights);
};

