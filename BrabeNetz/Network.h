#pragma once
#include "NetworkTopology.h"
#include "Properties.h"
#include <thread>

/// \brief An actual neural network
class network
{
public:
	////////////////
	//    ctor    //
	////////////////
	// initializerList: { 2, 3, 4, 1 }: 2 Input, 3 Hidden, 4 Hidden, 1 Output
	network(std::initializer_list<int> initializer_list, properties& properties);
	// initializerList: { 2, 3, 4, 1 }: 2 Input, 3 Hidden, 4 Hidden, 1 Output
	explicit network(network_topology& topology, properties& properties);
	// initializerList: { 2, 3, 4, 1 }: 2 Input, 3 Hidden, 4 Hidden, 1 Output
	explicit network(properties& properties);
	~network();

	////////////////
	// functions  //
	////////////////
	// Feed the network information and return the output layer with it's length "out_length"
	double* feed(double* input_values, const bool copy_input) const;
	// Backwards Propagate through the network, adjust weights and biases and return total output error
	double adjust(const double* expected_output) const;
	// Save the network's state to disk by serializing weights
	void save(std::string path = "state.nn") const;
	// Set the network's learning rate (should be 1/i, where i = train iterations so far)
	void set_learnrate(double value);
	// Build and set the network topology object of the current network's state
	network_topology& build_topology() const;
private:
	////////////////
	// properties //
	////////////////
	// Learning rate of this network (1/i, where i = train iterations so far)
	double learn_rate_;
	// Count of Layers in this network
	int layers_count_;
	// Count of Neurons in Layers (Left to right in Topology)
	int* neurons_count_;
	// Actual layers that contain nodes with their values
	double** layers_;
	// Each neuron's bias (has length of layers_count_, but every item in [0] is 0 because input layer has no bias)
	double** biases_;
	// Weight of each neuron's connection, 3D Array: [layer][neuron][connection]
	double*** weights_;
	// The network topology, only for logic representation and weights initialization
	network_topology& topology_;
	// Amount of cores/threads on this machine
	const int core_count_ = std::thread::hardware_concurrency();
	// The network's initializer properties
	properties& properties_;


	////////////////
	// functions  //
	////////////////
	// Init Network from this->topology_
	void init();
	// Forwards Propagate given input_values by one layer and return the new output layer with length of out_length
	double* to_next_layer(double* input_values, int input_length, int layer_index, int& out_length) const;
	// Fill neuron weights with this topology
	void fill_weights();
	// Delete weights array
	void delete_weights() const;
};
