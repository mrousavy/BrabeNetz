#include "stdafx.h"
#include "Layer.h"

Layer::Layer()
{
	this->Neurons = new std::vector<Neuron>();
}

Layer::~Layer()
{
	delete this->Neurons;
}

void Layer::AddNeuron(Neuron* neuron)
{
	this->Neurons->push_back(*neuron);
}