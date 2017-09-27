#pragma once
#include <vector>
#include "Neuron.h"

class Layer
{
public:
	Layer();
	~Layer();
	void AddNeuron(Neuron neuron);
	Neuron& NeuronAt(int index);
	int Size;
private:
	std::vector<Neuron> _neurons;
};
