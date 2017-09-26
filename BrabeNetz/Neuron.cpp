#include "stdafx.h"
#include "Neuron.h"

Neuron::Neuron()
{
	this->Connections = new std::vector<Connection*>();
}

Neuron::~Neuron()
{
	delete this->Connections;
}

void Neuron::AddConnection(Connection* connection)
{
	this->Connections->push_back(connection);
}