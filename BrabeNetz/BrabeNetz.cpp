#include "BrabeNetz.h"

network_result::network_result(const brabe_netz* network, std::vector<double>& values, const int feed_count)
	: values(values), feed_count(feed_count), network_(network)
{
}

double network_result::adjust(const std::vector<double>& expected_output) const
{
	if (this->network_->feed_count_ > this->feed_count)
		throw std::exception("Invalid use - adjust has to be called immediately after feeding!");

	return this->network_->adjust(expected_output.data());
}

brabe_netz::brabe_netz(std::initializer_list<int> initializer_list, properties& properties)
	: network_(initializer_list, properties), topology_(network_.build_topology()), output_size_(*initializer_list.end()),
	  input_size_(*initializer_list.begin()), feed_count_(0)
{
}

brabe_netz::brabe_netz(network_topology& topology, properties& properties)
	: network_(topology, properties), topology_(topology), output_size_(topology.layer_at(topology.size() - 1).size()),
	  input_size_(topology.layer_at(0).size()),
	  feed_count_(0)
{
}

brabe_netz::brabe_netz(properties& properties)
	: network_(properties), topology_(network_.build_topology()),
	  output_size_(topology_.layer_at(topology_.size() - 1).size()),
	  input_size_(topology_.layer_at(0).size()),
	  feed_count_(0)
{
}

brabe_netz::~brabe_netz()
{
}

network_result brabe_netz::feed(std::vector<double>& input_values) const
{
	double* output = this->network_.feed(input_values.data(), true);
	const int size = this->output_size_;
	return network_result(this, std::vector<double>(output, output + size), this->feed_count_);
}

void brabe_netz::save(const std::string path) const
{
	this->network_.save(path);
}

void brabe_netz::set_learnrate(const double value)
{
	this->network_.set_learnrate(value);
}

network_topology& brabe_netz::build_topology() const
{
	return this->network_.build_topology();
}

double brabe_netz::adjust(const double* expected_output) const
{
	return this->network_.adjust(expected_output);
}
