#include "stdafx.h"
#include "Layer.h"

layer::layer()
{
	this->size = 0;
}

layer::~layer()
{}

std::ostream& operator<<(std::ostream& os, layer& l)
{
	os << l.size;
	for (int i = 0; i < l.size; i++) // From 0 to last index
		os << l.neuron_at(i);
	return os;
}

std::istream& operator>> (std::istream& is, layer& l)
{
	is >> l.size;
	for (int i = 0; i < l.size; i++) // From last index to 0
		l.add_neuron(layer::read_neuron(is));
	return is;
}

neuron layer::read_neuron(std::istream& is)
{
	neuron n;
	is >> n;
	return n;
}


void layer::add_neuron(const neuron neuron)
{
	this->neurons_.push_back(neuron);
	this->size++;
}

neuron& layer::neuron_at(const int index)
{
	return this->neurons_.at(index);
}
