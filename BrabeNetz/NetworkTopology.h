#pragma once
#include <vector>
#include "Layer.h"

class network_topology
{
public:
	network_topology();
	~network_topology();
	void add_layer(layer layer);
	layer& layer_at(int index);
	int size;

	static network_topology random(std::vector<int> layers);
private:
	std::vector<layer> layers_;
};
