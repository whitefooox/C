#include "Figure3D.h"

double Cylinder::Volume()
{
	return h * F->Area();
}

Cylinder::Cylinder(Figure* _F, double _h)
{

	if (_h > 0)
	{
		h = _h;
	}
	else
	{
		h = 1;
	}
	F = _F->Clone();
}

Cylinder::~Cylinder()
{
	delete F;
}