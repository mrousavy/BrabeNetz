#pragma once
#include <vector>
using namespace std;

class Network
{
public:
	// ctor
	Network();
	~Network();

	// properties
	vector<int>* layers;

	// functions
	void Train(vector<double>* inputValues, vector<double>* weights, double expectedOutput);
};

