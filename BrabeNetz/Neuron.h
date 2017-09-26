#pragma once
#include <vector>
#include "Connection.h"

#ifndef Neuron_Included
#define Neuron_Included

class Connection;

class Neuron
{
public:
	Neuron();
	~Neuron();
	std::vector<Connection*>* Connections;
	void AddConnection(Connection* connection);
};
#endif