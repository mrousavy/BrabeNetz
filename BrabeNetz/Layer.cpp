#include "Layer.h"

layer::layer()
{
}

layer::~layer()
{
}

std::ostream& operator<<(std::ostream& os, layer& l)
{
	int size = l.size();
	os.write(reinterpret_cast<const char*>(&size), sizeof(size));
	for (int i = 0; i < size; i++) // From 0 to last index
		os << l.neuron_at(i);
	return os;
}

std::istream& operator>>(std::istream& is, layer& l)
{
	int size;
	is.read(reinterpret_cast<char*>(&size), sizeof(size));
	for (int i = 0; i < size; i++) // From last index to 0
		l.neurons_.push_back(layer::read_neuron(is));
	return is;
}

void layer::add_neuron(neuron& neuron)
{
	this->neurons_.push_back(neuron);
}

neuron& layer::neuron_at(const int index)
{
	return this->neurons_.at(index);
}
