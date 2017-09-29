#pragma once
#include <vector>
#include <ostream>
#include "Connection.h"

#ifndef NEURON_INCLUDED
#define NEURON_INCLUDED

class connection;

class neuron
{
	friend std::ostream& operator<<(std::ostream& os, neuron& n);
	friend std::istream& operator>>(std::istream& is, neuron& n);
public:
	neuron();
	~neuron();
	void add_connection(connection connection);
	connection& connection_at(int index);
	int size = 0;
	double value = 0;
	double error = 0;
	double bias = 0;
private:
	std::vector<connection> connections_;
	static connection read_connection(std::istream& is);
};
#endif
