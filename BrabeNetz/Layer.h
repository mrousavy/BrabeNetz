#pragma once
#include <vector>
#include "Neuron.h"

class layer
{
public:
	layer();
	~layer();
	void add_neuron(neuron neuron);
	neuron& neuron_at(int index);
	int size;
private:
	std::vector<neuron> neurons_;
};
