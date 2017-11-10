#pragma once
#include <vector>
#include <ostream>
#include "Neuron.h"

class layer
{
	friend std::ostream& operator<<(std::ostream& os, layer& l);
	friend std::istream& operator>>(std::istream& is, layer& l);
public:
	layer();
	~layer();
	void add_neuron(neuron& neuron);
	neuron& neuron_at(int index);
	int size;
private:
	std::vector<neuron> neurons_;
	static neuron read_neuron(std::istream& is);
};
