#include "Layer.h"

layer::layer()
{
	this->size = 0;
}

layer::~layer()
{
}

std::ostream& operator<<(std::ostream& os, layer& l)
{
	os.write(reinterpret_cast<const char*>(&l.size), sizeof(l.size));
	for (int i = 0; i < l.size; i++) // From 0 to last index
		os << l.neuron_at(i);
	return os;
}

std::istream& operator>>(std::istream& is, layer& l)
{
	is.read(reinterpret_cast<char*>(&l.size), sizeof(l.size));
	for (int i = 0; i < l.size; i++) // From last index to 0
		l.neurons_.push_back(layer::read_neuron(is));
	return is;
}

neuron layer::read_neuron(std::istream& is)
{
	neuron n;
	is >> n;
	return n;
}


void layer::add_neuron(neuron& neuron)
{
	this->neurons_.push_back(neuron);
	this->size = neurons_.size();
}

neuron& layer::neuron_at(const int index)
{
	return this->neurons_.at(index);
}
