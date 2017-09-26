#pragma once
#include <vector>
#include "Neuron.h"

class Layer
{
public:
	Layer();
	~Layer();
	std::vector<Neuron*>* Neurons;
	void AddNeuron(Neuron* neuron);
};
