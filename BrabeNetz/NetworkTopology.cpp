#include "stdafx.h"
#include "NetworkTopology.h"

#pragma region Connection
Connection::Connection(Neuron* from, Neuron* to, double initialWeight)
{
	this->From = from;
	this->To = to;
	this->Weight = initialWeight;
}

Connection::~Connection()
{}
#pragma endregion

#pragma region Neuron
Neuron::Neuron()
{
	this->Connections = new std::vector<Connection>();
}

Neuron::~Neuron()
{}
#pragma endregion

#pragma region Layer
Layer::Layer()
{
	this->Neurons = new std::vector<Neuron>();
}

Layer::~Layer()
{}
#pragma endregion

#pragma region NetworkTopology
NetworkTopology::NetworkTopology()
{
	this->Layers = new std::vector<Layer>();
}

NetworkTopology::~NetworkTopology()
{}
#pragma endregion

