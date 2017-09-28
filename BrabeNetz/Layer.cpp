#include "stdafx.h"
#include "Layer.h"

layer::layer()
{
	this->size = 0;
}

layer::~layer()
{}

void layer::add_neuron(const neuron neuron)
{
	this->neurons_.push_back(neuron);
	this->size++;
}

neuron& layer::neuron_at(const int index)
{
	return this->neurons_.at(index);
}