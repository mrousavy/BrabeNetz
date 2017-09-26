#include "stdafx.h"
#include "Neuron.h"

Neuron::Neuron()
{}

Neuron::~Neuron()
{}

void Neuron::AddConnection(Connection connection)
{
	this->Connections.push_back(connection);
}