#include "Network.h"
#include "Functions.h"
#include <ctime>
using namespace std;

#pragma region ctor

// ctor
network::network(initializer_list<int> initializer_list)
{
	srand(time(nullptr));

	if (initializer_list.size() < 3)
		throw
		"Initializer List can't contain less than 3 elements. E.g: { 2, 3, 4, 1 }: 2 Input, 3 Hidden, 4 Hidden, 1 Output";

	this->topology_ = network_topology::random(initializer_list);
	init(this->topology_);
}

network::network(network_topology& topology)
{
	srand(time(nullptr));
	init(topology);
}

network::network(const string path)
{
	srand(time(nullptr));
	load(path);
}

void network::init(network_topology& topology)
{
	this->topology_ = topology;
	this->layers_count_ = topology.size; // Count of layers = input (1) + hidden + output (1)
	this->layers_ = new double*[this->layers_count_];
	this->neurons_count_ = new int[this->layers_count_];

	for (int i = 0; i < this->layers_count_; i++)
	{
		const int layer_size = topology.layer_at(i).size; // Size of this layer (Neurons count)
		this->neurons_count_[i] = layer_size; // Set neuron count on this hidden layer
		this->layers_[i] = static_cast<double*>(malloc(sizeof(double) * layer_size));
	}
	fill_weights();
}

// dector
network::~network()
{
	// cleanup
	delete_weights();
	for (int i = 0; i < layers_count_; i++)
	{
		free(this->layers_[i]);
		delete[] this->biases_[i];
	}
	delete[] this->layers_;
	delete[] this->biases_;
	delete[] this->neurons_count_;
}

void network::set_learnrate(const double value)
{
	learn_rate_ = value;
}
#pragma endregion

#pragma region Forwards Propagation

// Feed the network information and return the output
double* network::feed(double* input_values) const
{
	double* values = input_values; // Values of current layer
	int* length = new int(this->neurons_count_[0]); // Copy input length to ptr variable
	for (int hidden_index = 1; hidden_index < this->layers_count_; hidden_index++) // Loop through each hidden layer
	{
		values = to_next_layer(values, *length, hidden_index, *length);
	}

	delete length;
	return values;
}

// This function focuses on only one layer, so in theory we have 1 input layer, the layer we focus on, and 1 output
// FORWARD-PROPAGATION ALGORITHM
double* network::to_next_layer(double* input_values, const int input_length, const int layer_index,
	int& out_length) const
{
	const int n_count = this->neurons_count_[layer_index]; // Count of neurons in the next layer (w/ layerIndex)
	double** weights = this->weights_[layer_index - 1]; // ptr to weights of neurons from prev. to this layer
	double* biases = this->biases_[layer_index]; // ptr to biases of neurons in the next layer
	double* layer = this->layers_[layer_index];

	for (int n = 0; n < n_count; n++) // Loop through each neuron "n" on the next layer
	{
		layer[n] = 0; // Reset neuron's value

		for (int ii = 0; ii < input_length; ii++) // Loop through each input value "ii"
		{
			layer[n] += input_values[ii] * weights[ii][n]; // Add Value * Weight to that neuron
		}

		layer[n] = squash(layer[n] + biases[n]); // Squash result
	}

	out_length = n_count;
	return layer;
}

#pragma endregion

#pragma region Backwards Propagation

// Train network and adjust weights to expectedOutput
double* network::train(double* input_values, double* expected_output, double& out_total_error) const
{
	const int length = this->neurons_count_[0]; // Count of input neurons
	if (this->layers_[0] != nullptr) free(this->layers_[0]);
	this->layers_[0] = static_cast<double*>(malloc(sizeof(double) * length));
	// Copy over inputs (we need this for adjust(..))
	for (int n = 0; n < length; n++) // Loop through each input neuron "n"
	{
		this->layers_[0][n] = input_values[n]; // TODO: Squash Input?
	}

	double* values = input_values; // Values of current layer
	int* values_length = new int(length); // Copy input length to variable
	for (int hidden_index = 1; hidden_index < this->layers_count_; hidden_index++) // Loop through each hidden layer + output
	{
		values = to_next_layer(values, *values_length, hidden_index, *values_length);
	}

	out_total_error = adjust(expected_output, values);
	delete values_length;
	return values;
}

// BACKWARDS-PROPAGATION ALGORITHM
double network::adjust(double* expected_output, double* actual_output) const
{
	const int output_length = this->neurons_count_[layers_count_ - 1]; // Count of neurons in output layer
	double** errors = static_cast<double**>(malloc(sizeof(double*) * layers_count_));
	// Each error value on the neurons (2D: [layer][neuron])
	errors[layers_count_ - 1] = static_cast<double*>(malloc(sizeof(double) * output_length));
	// Allocate output layer error size
	double error_sum = 0; // Sum of all errors on the output layer

	// Backpropagation loop for Output Layer only
	for (int on = 0; on < output_length; on++) // Loop through each neuron on the output layer "on"
	{
		const double error = expected_output[on] - actual_output[on]; // Error of this neuron in output layer
		error_sum += error;
		errors[layers_count_ - 1][on] = error; // Set error on output layer at neuron "on" to calculated error
	}

	// Backpropagation loop for Input and Hidden Layers
	for (int i = layers_count_ - 2; i > -1; i--) // Reverse-Loop through each hidden to input layer
	{
		const int neurons = this->neurons_count_[i]; // Count of neurons in this layer
		const int next_neurons = this->neurons_count_[i + 1]; // Count of neurons in next layer
		errors[i] = static_cast<double*>(malloc(sizeof(double) * neurons)); // Allocate this layer's errors array

		const bool worth = FORCE_MULTITHREADED || neurons * next_neurons > core_count * ITERS_PER_THREAD; // Worth the multithread-spawning?
#pragma omp parallel for if(worth) // OMP.Parallel loop on each CPU Core if worth the thread spawn
		for (int n = 0; n < neurons; n++) // Loop through each neuron on this layer
		{
			if (i > 0) // Only calculate error on hidden layers
			{
				double neuron_error = 0;
				for (int nn = 0; nn < next_neurons; nn++) // Loop through each neuron on next layer
				{
					// weights_[i][n][nn]	=> weights from this layer "i", neuron "n" to next layer's neuron "nn"
					// errors[i+1][nn]		=> errors from next layer at neuron "nn"
					neuron_error += weights_[i][n][nn] * errors[i + 1][nn];
				}
				errors[i][n] = neuron_error * squash_derivative(layers_[i][n]);
				this->biases_[i][n] += learn_rate_ * errors[i][n];
			}

			for (int nn = 0; nn < next_neurons; nn++) // Loop through each neuron on the next layer
			{
				// weights_[i][n][nn]	=> weights from this layer "i", neuron "n" to next layer's neuron "nn"
				// errors[i+1][nn]		=> errors from next layer at neuron "nn"
				// layers_[i][n]		=> neuron at index "n" on layer "i"
				this->weights_[i][n][nn] += learn_rate_ * errors[i + 1][nn] * layers_[i][n];
				// Update the weight with it's error & input
			}
		}
	}

	for (int i = 0; i < layers_count_; i++) // Loop through each layer (error)
		free(errors[i]);
	free(errors);
	return error_sum;
}

#pragma endregion

#pragma region State modification

void network::fill_weights()
{
	// layer weights has a reference on the heap
	if (this->weights_ != nullptr)
		delete_weights();

	const int count = this->layers_count_ - 1; // Count of layers with connections
	this->weights_ = new double**[count]; // init first dimension; count of layers with connections

	const int lcount = this->topology_.size; // Count of layers
	this->biases_ = new double*[lcount];
	this->weights_ = new double**[lcount];
#pragma omp parallel for
	for (int l = 0; l < lcount; l++) // Loop through each layer
	{
		layer& layer = this->topology_.layer_at(l);
		const int ncount = layer.size; // Count of neurons in this layer
		this->biases_[l] = new double[ncount];
		this->weights_[l] = new double*[ncount];
		for (int n = 0; n < ncount; n++) // Loop through each neuron in this layer
		{
			neuron& neuron = layer.neuron_at(n);

			this->biases_[l][n] = neuron.bias;
			const int ccount = neuron.size; // Count of connection on this neuron
			this->weights_[l][n] = new double[ccount];
			for (int c = 0; c < ccount; c++) // Loop through each connection on this neuron
			{
				this->weights_[l][n][c] = neuron.connection_at(c).weight;
			}
		}
	}
}

network_topology & network::build_topology()
{
	// TODO: Parallel for this?
	for (int i = 0; i < layers_count_ - 1; i++) // Loop through each layer until last hidden layer
	{
		layer& layer = this->topology_.layer_at(i);
		for (int n = 0; n < neurons_count_[i]; n++) // Loop through each neuron on this layer
		{
			neuron& neuron = layer.neuron_at(n);
			neuron.bias = biases_[i][n]; // Set bias to topology

			for (int nn = 0; nn < neurons_count_[i + 1]; nn++) // Loop through each neuron on the next layer
			{
				neuron.connection_at(nn).weight = weights_[i][n][nn]; // Set weight to topology
			}
		}
	}

	return this->topology_;
}

void network::save(const string path)
{
	network_topology::save(build_topology(), path);
}

void network::load(const string path)
{
	// ReSharper disable once CppMsExtBindingRValueToLvalueReference
	network_topology topology = network_topology::load(path);
	init(topology);
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

#pragma endregion
