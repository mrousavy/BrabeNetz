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
	void AddConnection(Connection connection);
	Connection& ConnectionAt(int index);
	int Size;
	// TODO: Neuron.h Bias/Error
	double Error;
	double Bias;
private:
	std::vector<Connection> _connections;
};
#endif