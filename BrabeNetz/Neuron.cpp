#include "stdafx.h"
#include "Neuron.h"

Neuron::Neuron()
{
	this->Size = 0;
}

Neuron::~Neuron()
{}

void Neuron::AddConnection(Connection connection)
{
	this->_connections.push_back(connection);
	this->Size++;
}

Connection& Neuron::ConnectionAt(int index)
{
	return this->_connections.at(index);
}