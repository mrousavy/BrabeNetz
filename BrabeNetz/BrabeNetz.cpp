#include "BrabeNetz.h"

const double NetworkResult::adjust(const std::vector<double>& expected_output) const
{
	if (this->network._feed_count != this->feed_count)
		throw std::exception("Invalid use - adjust has to be called immediately after feeding!");

	return this->network.adjust(expected_output, this->values);
}

BrabeNetz::BrabeNetz(std::initializer_list<int> initializer_list, properties & properties)
	: _network(initializer_list, properties), _feed_count(0), _output_size(*initializer_list.end())
{}

BrabeNetz::BrabeNetz(network_topology & topology, properties & properties)
	: _network(topology, properties), _feed_count(0),
	_output_size(topology.layer_at(topology.size() - 1).size())
{}

BrabeNetz::BrabeNetz(properties & properties)
	: _network(properties), _feed_count(0)
{
	auto topology = _network.build_topology();
	_output_size = topology.layer_at(topology.size() - 1).size();
}

BrabeNetz::~BrabeNetz()
{}

const std::vector<double> BrabeNetz::feed(std::vector<double>& input_values) const
{
	double* output = this->_network.feed(input_values.data());
	int size = this->_output_size;
	return std::vector<double>(output, output + size);
}

void BrabeNetz::save(std::string path) const
{
	this->_network.save(path);
}

void BrabeNetz::set_learnrate(double value)
{
	this->_network.set_learnrate(value);
}

network_topology & BrabeNetz::build_topology() const
{
	return this->_network.build_topology();
}

const double BrabeNetz::adjust(double* expected_output, double* actual_output) const
{
	return this->_network.adjust(expected_output, actual_output);
}
