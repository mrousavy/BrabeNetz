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

	static NetworkTopology Random(std::vector<int> layers);
private:
	std::vector<Layer> _layers;
};
