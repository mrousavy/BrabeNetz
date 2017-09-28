#pragma once
#include "NetworkTopology.h"
#include <vector>
using namespace std;

// Specifies the value each weight gets adjusted by on training
#define ADJUST_WEIGHTS_BY 0.002
// Maximum delta of actual and expected values until stop training
#define MAX_DELTA 0.01

class network
{
public:
	////////////////
	//    ctor    //
	////////////////
	// initializerList: { 2, 3, 4, 1 }: 2 Input, 3 Hidden, 4 Hidden, 1 Output
	network(initializer_list<int> initializer_list);
	// initializerList: { 2, 3, 4, 1 }: 2 Input, 3 Hidden, 4 Hidden, 1 Output
	explicit network(network_topology& topology);
	~network();

	////////////////
	// functions  //
	////////////////
	// Feed the network information and train it to adjust to the expected output (returns output error)
	double train(double* input_values, int length, double expected_output);
	// Feed the network information and return the output layer
	double* feed(double* input_values, int length, int& out_length);
	// Save the network's state to disk by serializing weights
	void save(string path);
	// Load the network's state from disk by deserializing and loading weights
	void load(string path);

private:
	////////////////
	// properties //
	////////////////
	// Count of Layers in this network
	int layers_count_;
	// Count of Neurons in Layers (Left to right in Topology)
	int* neurons_count_;
	// Actual layers that contain nodes with their values
	double** layers_;
	// Each neuron's bias
	double** biases_;
	// Each neuron's error values
	double** errors_;
	// Weight of each neuron's connection, 3D Array: [layer][neuron][connection]
	double*** weights_;
	// The network topology, only for logic representation and weights initialization
	network_topology topology_;


	////////////////
	// functions  //
	////////////////
	// Init Network
	void init(network_topology& topology);
	// Put inputValues into layer at given layerIndex with squashing, etc and return layer's values
	double* to_next_layer(double* input_values, int input_length, int layer_index, int& out_length);
	// Adjust Network's weights and Biases
	void adjust(double expected, double actual);
	// Fill neuron weights with given values
	void fill_weights(network_topology& topology);
	// Delete weights array
	void delete_weights();
};

