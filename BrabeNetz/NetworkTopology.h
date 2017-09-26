#pragma once
#include <vector>
#include "Layer.h"

class NetworkTopology
{
public:
	NetworkTopology();
	~NetworkTopology();
	std::vector<Layer*>* Layers;
	void AddLayer(Layer* layer);
};
