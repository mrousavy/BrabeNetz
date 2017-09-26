#include "stdafx.h"
#include "Layer.h"

Layer::Layer()
{}

Layer::~Layer()
{}

void Layer::AddNeuron(Neuron neuron)
{
	this->Neurons.push_back(neuron);
}