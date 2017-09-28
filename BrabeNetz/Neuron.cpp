#include "stdafx.h"
#include "Neuron.h"

neuron::neuron()
{}

neuron::~neuron()
{}

void neuron::add_connection(connection connection)
{
	this->connections_.push_back(connection);
	this->size++;
}

connection& neuron::connection_at(int index)
{
	return this->connections_.at(index);
}