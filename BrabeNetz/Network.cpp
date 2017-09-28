#include "stdafx.h"
#include "Network.h"
#include <ctime>
#include "Functions.h"
using namespace std;

// TODO: REMOVE INCLUDES
#include "Extensions.h"

// ctor
network::network(initializer_list<int> initializer_list)
{
	srand(time(nullptr));

	if (initializer_list.size() < 3)
		throw
			"Initializer List can't contain less than 3 elements. E.g: { 2, 3, 4, 1 }: 2 Input, 3 Hidden, 4 Hidden, 1 Output";

	vector<int> input_vector; // clone initializer list to vector
	input_vector.insert(input_vector.end(), initializer_list.begin(), initializer_list.end());

	this->topology_ = network_topology::random(input_vector);
	init(this->topology_);
	fill_weights(this->topology_);
}

network::network(network_topology& topology)
{
	srand(time(nullptr));

	init(topology);
	fill_weights(topology);
}

void network::init(network_topology& topology)
{
	this->layers_count_ = topology.size; // Count of layers = input (1) + hidden + output (1)
	this->layers_ = new double*[this->layers_count_];
	this->neurons_count_ = new int[this->layers_count_];

	for (int i = 0; i < this->layers_count_; i++)
	{
		const int layer_size = topology.layer_at(i).size; // Size of this layer (Neurons count)
		this->neurons_count_[i] = layer_size; // Set neuron count on this hidden layer
		this->layers_[i] = new double[layer_size];
	}
}

// dector
network::~network()
{
	// cleanup
	delete_weights();
	delete[] this->neurons_count_;
}

// Train network and adjust weights to expectedOutput
double network::train(double* input_values, const int length, double* expected_output, int expected_length)
{
	int* output_length = new int;
	double* output_layer = feed(input_values, length, *output_length);

	vector<double> vec = extensions::to_vector<double>(output_layer, *output_length); // TODO: REMOVE TOVECTOR

	double sum = 0;
	for (int i = 0; i < *output_length; i++) // Loop through each neuron in output layer
	{
		sum += squash(rectify(output_layer[i])); // Squash and ReLU it (keep if positive, 0 if negative; uint)
	}

	double distance = euclidean_dist(output_layer, expected_output, *output_length);

	// TODO: RETURN LAST ERROR
	return vec.at(0);
}

// Feed the network information and return the output
double* network::feed(double* input_values, const int length, int& out_length) const
{
	double* values = input_values; // Values of current layer
	int* values_length = new int(length); // Copy input length to variable
	for (int hidden_index = 1; hidden_index < this->layers_count_; hidden_index++) // Loop through each hidden layer
	{
		values = to_next_layer(values, *values_length, hidden_index, *values_length);
		vector<double> vec = extensions::to_vector<double>(values, *values_length); // TODO: REMOVE TOVECTOR
	}

	double sum = 0;
	for (int i = 0; i < *values_length; i++) // Loop through each neuron in output layer
	{
		sum += squash(rectify(values[i])); // Squash and ReLU it (keep if positive, 0 if negative; uint)
	}

	out_length = *values_length;
	return values;
}

// This function focuses on only one layer, so in theory we have 1 input layer, the layer we focus on, and 1 output
double* network::to_next_layer(double* input_values, const int input_length, const int layer_index,
                               int& out_length) const
{
	vector<double> vec = extensions::to_vector<double>(input_values, input_length); // TODO: REMOVE TOVECTOR
	const int n_count = this->neurons_count_[layer_index]; // Count of neurons in the next layer (w/ layerIndex)
	double** weights = this->weights_[layer_index - 1]; // ptr to weights of neurons in this layer
	double* biases = this->biases_[layer_index]; // ptr to biases of neurons in the next layer
	double* layer = this->layers_[layer_index];

	for (int n = 0; n < n_count; n++) // Loop through each neuron "n" on the next layer
	{
		layer[n] = 0; // Reset neuron's value

		for (int ii = 0; ii < input_length; ii++) // Loop through each input value "ii"
		{
			layer[n] += input_values[ii] * weights[ii][n]; // Add Value * Weight to that neuron
		}

		const double result = layer[n] + biases[n];
		layer[n] = squash(result); // Squash result
	}

	out_length = n_count;
	return layer;
}

// TODO: Check if this works
void network::fill_weights(network_topology& topology)
{
	this->topology_ = topology;

	// layer weights has a reference on the heap
	if (this->weights_ != nullptr)
		delete_weights();

	const int count = this->layers_count_ - 1; // Count of layers with connections
	this->weights_ = new double**[count]; // init first dimension; count of layers with connections

	const int lcount = topology.size; // Count of layers
	this->biases_ = new double*[lcount];
	this->weights_ = new double**[lcount];
	for (int l = 0; l < lcount; l++) // Loop through each layer
	{
		layer& layer = topology.layer_at(l);
		const int ncount = layer.size; // Count of neurons in this layer
		this->biases_[l] = new double[ncount];
		this->weights_[l] = new double*[ncount];
		for (int n = 0; n < ncount; n++) // Loop through each neuron in this layer
		{
			neuron& neuron = layer.neuron_at(n);

			this->biases_[l][n] = neuron.bias;
			const int ccount = neuron.size; // Count of connection on this neuron
			this->weights_[l][n] = new double[ccount];
			for (int c = 0; c < neuron.size; c++) // Loop through each connection on this neuron
			{
				this->weights_[l][n][c] = neuron.connection_at(c).weight;
			}
		}
	}
}

void network::adjust(const double expected, const double actual)
{
	double error = get_error(expected, actual); // Error on output layer
}

void network::save(string path)
{
	// TODO: Serialize NetworkTopology and save it
}

void network::load(string path)
{
	// TODO: Deserialize NetworkTopology and load it
}

void network::delete_weights() const
{
	for (int i = 0; i < this->layers_count_ - 1; i++) // Loop through each layer
	{
		const int lneurons = this->neurons_count_[i];

		for (int n = 0; n < lneurons; n++) // Loop through each neuron in this layer
		{
			delete[] this->weights_[i][n]; // Delete all connections on this neuron
		}
		delete[] this->weights_[i]; // Delete all neurons on this layer
	}
	delete[] this->weights_; // Delete layer
}
