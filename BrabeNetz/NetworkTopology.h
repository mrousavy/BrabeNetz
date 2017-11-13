#pragma once
#include "Layer.h"
#include <vector>
#include <string>

class network_topology
{
	friend std::ostream& operator<<(std::ostream& os, network_topology& nt);
	friend std::istream& operator>>(std::istream& is, network_topology& nt);
public:
	network_topology();
	~network_topology();
	void add_layer(layer& layer);
	layer& layer_at(int index);

	inline int size()
	{
		return (int)layers_.size();
	}

	static network_topology random(std::vector<int> layers);
	static network_topology load(std::string path);
	static void save(network_topology& topology, std::string path);
	static int clear(const std::string path);
private:
	std::vector<layer> layers_;
	static layer read_layer(std::istream& is);
};
