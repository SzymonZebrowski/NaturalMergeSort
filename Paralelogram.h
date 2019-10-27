#pragma once
#include <math.h>
#include <iostream>
#include <sstream>

class Paralelogram
{
	float a;
	float b;
	float angle;

public:
	Paralelogram();
	Paralelogram(float a_, float b_, float angle_);

	float get_field() const;

	std::string to_string() const;

	friend std::ostream& operator<< (std::ostream& o, const Paralelogram& obj);

	friend std::ostream& operator<< (std::ostream& o, const Paralelogram* obj);
};
