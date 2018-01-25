#pragma once
#include "NetworkTopology.h"
#include "Properties.h"
#include "Network.h"

class brabe_netz;

/// <summary>
///		A Neural Network's output result
/// </summary>
struct network_result
{
public:
	/// <summary>
	///		Create a new instance of the network result
	/// </summary>
	network_result(const brabe_netz* network,
	               std::vector<double>& values,
	               const int feed_count);

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
	/// <param name="expected_output">
	///		The expected output of the neural network which
	///		the network will train towards/adjust to
	/// </param>
	/// <returns>
	///		Returns the neural network's total error value
	/// </returns>
	double adjust(const std::vector<double>& expected_output) const;
private:
	const brabe_netz* network_;
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
class brabe_netz
{
public:
	////////////////
	//    ctor    //
	////////////////

	/// <summary>
	///		Construct a new neural network with the given network size
	///		and randomize all base weights and biases
	/// </summary>
	/// <param name="initializer_list">
	///		The size of the neural network's layers and neurons
	/// </param>
	/// <param name="properties">
	///		Additional Parameters for the neural network
	/// </param>
	/// <example>An example constructor call for a {2,3,4,1} network
	/// <code>
	/// properties properties;
	/// BrabeNetz network({ 2, 3, 4, 1 }, properties);
	/// </code>
	/// </example>
	brabe_netz(std::initializer_list<int> initializer_list, properties& properties);

	/// <summary>
	///		Construct a new neural network with the given network
	///		topology and import it's existing weights and biases
	/// </summary>
	/// <param name="topology">
	///		A built topology with set weights and biases
	/// </param>
	/// <param name="properties">
	///		Additional Parameters for the neural network
	/// </param>
	explicit brabe_netz(network_topology& topology, properties& properties);

	/// <summary>
	///		Construct a new neural network with the given network
	///		topology and load the neural network state from the 
	///		file specified in <c>properties.state_file</c>
	/// </summary>
	/// <param name="properties">
	///		Additional Parameters for the neural network - 
	///		This constructor will load from the state file
	///		located at <c>properties.state_file</c>
	/// </param>
	explicit brabe_netz(properties& properties);

	/// <summary>
	///		Destroy the neural network and clear memory
	/// </summary>
	~brabe_netz();


	////////////////
	// functions  //
	////////////////

	/// <summary>
	///		Feed the network input values and forward propagate
	///		through all neurons to estimate a possible output
	/// </summary>
	/// <param name="input_values">
	///		The input layer's values (Must be exact size as the
	///		network's input layer size)
	/// </param>
	/// <returns>
	///		Returns the neural network's result. Use this to
	///		adjust and backpropagate through the network
	/// </returns>
	network_result feed(std::vector<double>& input_values) const;

	/// <summary>
	///		Save the network's state to disk by serializing weights
	/// </summary>
	/// <param name="path">
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
	/// <param name="value">
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

	friend double network_result::adjust(const std::vector<double>& expected_output) const;
	friend network_result::network_result(const brabe_netz* network, std::vector<double>& values, const int feed_count);
private:
	network network_;
	network_topology& topology_;
	const int output_size_;
	const int input_size_;
	int feed_count_;

	double adjust(const double* expected_output) const;
};
