#pragma once
#include <ostream>
#include <istream>

class connection
{
	friend std::ostream& operator<<(std::ostream& os, const connection& c);
	friend std::istream& operator>>(std::istream& is, connection& c);
public:
	connection();
	~connection();
	connection(const double weight);
	double weight = 1;
};
