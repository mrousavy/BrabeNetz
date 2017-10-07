#pragma once
#include "Neuron.h"
#include <ostream>
#include <istream>

#ifndef CONNECTION_INCLUDED
#define CONNECTION_INCLUDED

class neuron;

class connection
{
	friend std::ostream& operator<<(std::ostream& os, const connection& c);
	friend std::istream& operator>>(std::istream& is, connection& c);
public:
	connection();
	~connection();
	double weight;
};

#endif
