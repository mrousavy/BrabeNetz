#pragma once
#include <ostream>
#include <istream>

class connection
{
	friend std::ostream& operator<<(std::ostream& os, const connection& c);
	friend std::istream& operator>>(std::istream& is, connection& c);
public:
	connection();
	explicit connection(double weight);
	~connection();
	double weight;
};
