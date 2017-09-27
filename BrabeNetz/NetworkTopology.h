#pragma once
#include <vector>
#include "Layer.h"

class NetworkTopology
{
public:
	NetworkTopology();
	~NetworkTopology();
	void AddLayer(Layer layer);
	Layer& LayerAt(int index);
	int Size;
private:
	std::vector<Layer> _layers;
};
