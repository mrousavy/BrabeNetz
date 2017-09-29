#include "stdafx.h"
#include "Neuron.h"

neuron::neuron()
{
}

neuron::~neuron()
{
}

std::ostream& operator<<(std::ostream& os, neuron& n)
{
	os.write(reinterpret_cast<const char*>(&n.size), sizeof(n.size));
	os.write(reinterpret_cast<const char*>(&n.bias), sizeof(n.bias));
	for (int i = 0; i < n.size; i++) // From 0 to last index
		os << n.connection_at(i);
	return os;
}

std::istream& operator>>(std::istream& is, neuron& n)
{
	is.read(reinterpret_cast<char*>(&n.size), sizeof(n.size));
	is.read(reinterpret_cast<char*>(&n.bias), sizeof(n.bias));
	for (int i = 0; i < n.size; i++) // From last index to 0
		n.connections_.push_back(neuron::read_connection(is));
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
	this->size = connections_.size();
}

connection& neuron::connection_at(const int index)
{
	return this->connections_.at(index);
}
