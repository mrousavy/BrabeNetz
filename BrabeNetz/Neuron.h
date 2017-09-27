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
	int Size = 0;
	double Value = 0;
	double Error = 0;
	double Bias = 0;
private:
	std::vector<Connection> _connections;
};
#endif