#include "stdafx.h"
#include "Layer.h"

Layer::Layer()
{
	this->Size = 0;
}

Layer::~Layer()
{}

void Layer::AddNeuron(Neuron neuron)
{
	this->_neurons.push_back(neuron);
	this->Size++;
}

Neuron& Layer::NeuronAt(int index)
{
	return this->_neurons.at(index);
}