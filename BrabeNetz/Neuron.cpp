#include "stdafx.h"
#include "Neuron.h"

neuron::neuron()
{}

neuron::~neuron()
{}

std::ostream& operator<<(std::ostream& os, neuron& n)
{
	os << n.size;
	os << n.bias;
	for (int i = 0; i < n.size; i++) // From 0 to last index
		os << n.connection_at(i);
	return os;
}

std::istream& operator>> (std::istream& is, neuron& n)
{
	is >> n.size;
	is >> n.bias;
	for (int i = 0; i < n.size; i++) // From last index to 0
		n.add_connection(neuron::read_connection(is));
	return is;
}

connection neuron::read_connection(std::istream& is)
{
	connection c;
	is >> c;
	return c;
}

void neuron::add_connection(const connection connection)
{
	this->connections_.push_back(connection);
	this->size++;
}

connection& neuron::connection_at(const int index)
{
	return this->connections_.at(index);
}
