#include "stdafx.h"
#include "Layer.h"

layer::layer()
{
	this->size = 0;
}

layer::~layer()
{}

void layer::add_neuron(neuron neuron)
{
	this->neurons_.push_back(neuron);
	this->size++;
}

neuron& layer::neuron_at(int index)
{
	return this->neurons_.at(index);
}