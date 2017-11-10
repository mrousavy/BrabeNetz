#pragma once
#include "NetworkTopology.h"
#include <thread>
using namespace std;

// Default learning rate for the backpropagation weights/bias adjusting
#define LEARNING_RATE 0.01
// Filename for the state file
#define STATE_FILE "state.nn"
// Force use of multithreading for backpropagation (only use on larger layers, experiment yourself)
#define FORCE_MULTITHREADED false
// Amount of iterations each thread is expected to do (thread spawning takes ~270.000ns, the loop ~250ns)
#define ITERS_PER_THREAD 600

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
	// initializerList: { 2, 3, 4, 1 }: 2 Input, 3 Hidden, 4 Hidden, 1 Output
	explicit network(string state_path);
	~network();

	////////////////
	// functions  //
	////////////////
	// Feed the network information and train it to adjust to the expected output (returns network output)
	double* train(double* input_values, double* expected_output, double& out_total_error) const;
	// Feed the network information and return the output layer with it's length "out_length"
	double* feed(double* input_values) const;
	// Save the network's state to disk by serializing weights
	void save(string path = STATE_FILE);
	// Set the network's learning rate (should be 1/i, where i = train iterations so far)
	void set_learnrate(double value);
	// Build and set the network topology object of the current network's state
	network_topology& build_topology();
private:
	////////////////
	// properties //
	////////////////
	// Learning rate of this network (1/i, where i = train iterations so far)
	double learn_rate_ = LEARNING_RATE;
	// Count of Layers in this network
	int layers_count_;
	// Count of Neurons in Layers (Left to right in Topology)
	int* neurons_count_;
	// Actual layers that contain nodes with their values
	double** layers_;
	// Each neuron's bias (has length of layers_count_, but every item in [0] is 0 because input layer has no bias)
	double** biases_;
	// Each neuron's error values
	double** errors_;
	// Weight of each neuron's connection, 3D Array: [layer][neuron][connection]
	double*** weights_;
	// The network topology, only for logic representation and weights initialization
	network_topology topology_;
	// Amount of cores/threads on this machine
	const int core_count = std::thread::hardware_concurrency();


	////////////////
	// functions  //
	////////////////
	// Init Network
	void init(network_topology& topology);
	// Load the network's state from disk by deserializing and loading weights/biases
	void load(string path = STATE_FILE);
	// Forwards Propagate given input_values by one layer and return the new output layer with length of out_length
	double* to_next_layer(double* input_values, int input_length, int layer_index, int& out_length) const;
	// Backwards Propagate through the network, adjust weights and biases and return total output error
	double adjust(double* expected_output, double* actual_output) const;
	// Fill neuron weights with this topology
	void fill_weights();
	// Delete weights array
	void delete_weights() const;
};
