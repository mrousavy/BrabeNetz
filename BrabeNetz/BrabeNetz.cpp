#include "BrabeNetz.h"

network_result::network_result(const brabenetz* network, std::vector<double>* values, const int feed_count)
	: feed_count(feed_count), values_(values), network_(network)
{
}

network_result::~network_result()
{
	delete values_;
}

const std::vector<double>& network_result::values() const noexcept
{
	return *values_;
}


double network_result::adjust(const std::vector<double>& expected_output) const
{
	if (this->network_->feed_count_ != this->feed_count)
		throw std::runtime_error("Invalid use - adjust has to be called immediately after feeding!");

	return this->network_->adjust(expected_output.data());
}

brabenetz::brabenetz(std::initializer_list<int> initializer_list, properties& properties)
	: network_(initializer_list, properties), topology_(network_.build_topology()), 
	  output_size_(std::vector<int>(initializer_list).back()),
	  input_size_(*initializer_list.begin()), feed_count_(0)
{
}

brabenetz::brabenetz(network_topology& topology, properties& properties)
	: network_(topology, properties), topology_(topology), output_size_(topology.layer_at(topology.size() - 1).size()),
	  input_size_(topology.layer_at(0).size()),
	  feed_count_(0)
{
}

brabenetz::brabenetz(properties& properties)
	: network_(properties), topology_(network_.build_topology()),
	  output_size_(topology_.layer_at(topology_.size() - 1).size()),
	  input_size_(topology_.layer_at(0).size()),
	  feed_count_(0)
{
}

brabenetz::~brabenetz()
{
}

network_result brabenetz::feed(std::vector<double>& input_values)
{
	if (input_values.size() != this->input_size_)
		throw std::invalid_argument("The input values vector does not match the network's input layer's size!");

	double* output = this->network_.feed(input_values.data(), true);
	this->feed_count_++;
	return network_result(this, new std::vector<double>(output, output + this->output_size_), this->feed_count_);
}

void brabenetz::save(const std::string path) const
{
	if (path.length() < 1)
		throw std::invalid_argument("The given path cannot be empty!");

	this->network_.save(path);
}

void brabenetz::set_learnrate(const double value) noexcept
{
	if (value < 0.0)
		throw std::invalid_argument("The learn rate can't be less than 0!");

	this->network_.set_learnrate(value);
}

network_topology& brabenetz::build_topology() const
{
	return this->network_.build_topology();
}

double brabenetz::adjust(const double* expected_output) const noexcept
{
	return this->network_.adjust(expected_output);
}
