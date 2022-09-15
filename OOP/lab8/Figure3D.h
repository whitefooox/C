#pragma once
#include "Figure.h"
#include "Exception.h"
class Figure3D
{
public:
	virtual double CalcVolume() = 0;
};

template<typename typeFigure>
class Cylinder : public Figure3D
{
private:
	typeFigure* f;
	double h;

public:
	Cylinder(typeFigure* f, double h) 
	{
		if (h > 0)
		{
			this->h = h;
			this->f = new typeFigure(*f);
		}
		else throw Exception(1, "Error creating cylinder");
	}
	double CalcVolume()
	{
		return h * f->CalcArea();
	}
	~Cylinder()
	{
		delete f;
	};
};