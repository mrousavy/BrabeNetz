#include "BrabeNetz.h"

NetworkResult::NetworkResult(const BrabeNetz* network, std::vector<double>& values, const int feed_count)
	: values(values), feed_count(feed_count), _network(network)
{}

const double NetworkResult::adjust(const std::vector<double>& expected_output) const
{
	if (this->_network->_feed_count > this->feed_count)
		throw std::exception("Invalid use - adjust has to be called immediately after feeding!");

	return this->_network->adjust(expected_output.data(), this->values.data());
}

BrabeNetz::BrabeNetz(std::initializer_list<int> initializer_list, properties & properties)
	: _network(initializer_list, properties), _feed_count(0), _topology(_network.build_topology()),
	_output_size(*initializer_list.end()), _input_size(*initializer_list.begin())
{}

BrabeNetz::BrabeNetz(network_topology& topology, properties& properties)
	: _network(topology, properties), _feed_count(0), _topology(topology),
	_output_size(topology.layer_at(topology.size() - 1).size()),
	_input_size(topology.layer_at(0).size())
{}

BrabeNetz::BrabeNetz(properties & properties)
	: _network(properties), _feed_count(0), _topology(_network.build_topology()),
	_output_size(_topology.layer_at(_topology.size() - 1).size()),
	_input_size(_topology.layer_at(0).size())
{}

BrabeNetz::~BrabeNetz()
{}

const NetworkResult BrabeNetz::feed(std::vector<double>& input_values) const
{
	double* output = this->_network.feed(input_values.data(), true);
	int size = this->_output_size;
	return NetworkResult(this, std::vector<double>(output, output + size), this->_feed_count);
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

const double BrabeNetz::adjust(const double* expected_output, const double* actual_output) const
{
	return this->_network.adjust(expected_output, actual_output);
}
