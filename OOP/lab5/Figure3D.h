#pragma once
#include "Figure.h"
class Figure3D
{
public:
	virtual double Volume() = 0;
};

class Cylinder : public Figure3D
{
private:
	double h;
	Figure* F;
public:
	double Volume();

	Cylinder(Figure* F, double h);
	~Cylinder();
};