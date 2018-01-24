#pragma once
#include "NetworkTopology.h"
#include "Properties.h"
#include "Network.h"

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
};

