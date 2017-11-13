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
	int size = 0;
private:
	std::vector<neuron> neurons_;

	static inline neuron read_neuron(std::istream& is)
	{
		neuron n;
		is >> n;
		return n;
	}
};
