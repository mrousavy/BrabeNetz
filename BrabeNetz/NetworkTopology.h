#pragma once
#include <vector>


class Connection
{
public:
	Connection(Neuron* from, Neuron* to, double initialWeight);
	~Connection();
	Neuron* From;
	Neuron* To;
	double Weight;
};

class Neuron
{
public:
	Neuron();
	~Neuron();
	std::vector<Connection>* Connections;
	void AddConnection(Connection* connection);
};

class Layer
{
public:
	Layer();
	~Layer();
	std::vector<Neuron>* Neurons;
	void AddNeuron(Neuron* neuron);
};


class NetworkTopology
{
public:
	NetworkTopology();
	~NetworkTopology();
	std::vector<Layer>* Layers;
	void AddLayer(Layer* layer);
};