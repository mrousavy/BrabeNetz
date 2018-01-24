#pragma once
#include "NetworkTopology.h"
#include "Properties.h"
#include "Network.h"

/// <summary>
///		A Neural Network's output result
/// </summary>
struct NetworkResult
{
public:
	/// <summary>
	///		The actual output layer's values
	/// </summary>
	const std::vector<double>& values;
	/// <summary>
	///		A counter indicating the amount of
	///		forward propagations that have taken
	///		place
	/// </summary>
	const int feed_count;

	/// <summary>
	///		Backwards propagate through the whole
	///		network to adjust wrong neurons for
	///		result trimming
	/// </summary>
	/// <remarks>
	///		You can only call <c>adjust(..)</c> immediately
	///		after retrieving this NetworkResult
	/// </remarks>
	/// <param name='expected_output'>
	///		The expected output of the neural network which
	///		the network will train towards/adjust to
	/// </param>
	/// <returns>
	///		Returns the neural network's total error value
	/// </returns>
	const double adjust(const std::vector<double>& expected_output) const;
private:
	BrabeNetz & network;
};

/// <summary>
///		A Neural Network proxy class - 
///		This is a wrapper for the actual Neural Network
///		with modern C++ functions.
/// </summary>
/// <remarks>
///		Be aware that this network wrapper might be
///		a bit slower than the raw network, but is by
///		far easier and better to use and read.
/// </remarks>
class BrabeNetz
{
public:
	////////////////
	//    ctor    //
	////////////////

	/// <summary>
	///		Construct a new neural network with the given network size
	///		and randomize all base weights and biases
	/// </summary>
	/// <param name='initializer_list'>
	///		The size of the neural network's layers and neurons
	/// </param>
	/// <param name='properties'>
	///		Additional Parameters for the neural network
	/// </param>
	/// <example>An example constructor call for a {2,3,4,1} network
	/// <code>
	/// properties properties;
	/// BrabeNetz network({ 2, 3, 4, 1 }, properties);
	/// </code>
	/// </example>
	BrabeNetz(std::initializer_list<int> initializer_list, properties& properties);

	/// <summary>
	///		Construct a new neural network with the given network
	///		topology and import it's existing weights and biases
	/// </summary>
	/// <param name='topology'>
	///		A built topology with set weights and biases
	/// </param>
	/// <param name='properties'>
	///		Additional Parameters for the neural network
	/// </param>
	explicit BrabeNetz(network_topology& topology, properties& properties);

	/// <summary>
	///		Construct a new neural network with the given network
	///		topology and load the neural network state from the 
	///		file specified in <c>properties.state_file</c>
	/// </summary>
	/// <param name='properties'>
	///		Additional Parameters for the neural network - 
	///		This constructor will load from the state file
	///		located at <c>properties.state_file</c>
	/// </param>
	explicit BrabeNetz(properties& properties);

	/// <summary>
	///		Destroy the neural network and clear memory
	/// </summary>
	~BrabeNetz();

	////////////////
	// functions  //
	////////////////

	/// <summary>
	///		Feed the network input values and forward propagate
	///		through all neurons to estimate a possible output
	/// </summary>
	/// <param name='input_values'>
	///		The input layer's values (Must be exact size as the
	///		network's input layer size)
	/// </param>
	/// <returns>
	///		Returns the neural network's output layer's values.
	/// </returns>
	const std::vector<double> feed(std::vector<double>& input_values) const;

	/// <summary>
	///		Save the network's state to disk by serializing weights
	/// </summary>
	/// <param name='path'>
	///		The path to the file which will be created or
	///		written to
	/// </param>
	void save(std::string path = "state.nn") const;

	/// <summary>
	///		Set the network's learning rate
	/// </summary>
	/// <remarks>
	///		It is good practice and generally recommended to use
	///		the one divided by the train count, so the learn rate
	///		decreases the more often you train
	/// </remarks>
	/// <param name='value'>
	///		The new learn rate
	/// </param>
	void set_learnrate(double value);
	/// <summary>
	///		Build and set the network topology object of the current
	///		network's state
	/// </summary>
	/// <returns>
	///		Returns the neural network's topology which indicates
	///		the network structure & size, and it's weights and biases
	/// </returns>
	network_topology& build_topology() const;

	friend const double NetworkResult::adjust(const std::vector<double>& expected_output) const;

private:
	network _network;
	int _feed_count;

	const double adjust(const std::vector<double>& expected_output) const;
};

