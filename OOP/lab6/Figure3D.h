#pragma once
#include "Figure.h"
class Figure3D
{
public:
	virtual double CalcVolume() = 0;
};

class Cylinder : public Figure3D
{
protected:
	Figure* f;
	Cylinder(Figure* f, double h);

private:
	double h;

public:
	double CalcVolume();
	virtual ~Cylinder();
};

class CircleCylinder : public Cylinder
{	
private:
	CircleCylinder(Circle* f, double h);

public:
	static CircleCylinder* CreateInstance(Circle* f, double h);
	double GetRadius();
	~CircleCylinder();
};

class TriangleCylinder : public Cylinder
{
private:
	TriangleCylinder(Triangle* f, double h);

public:
	static TriangleCylinder* CreateInstance(Triangle* f, double h);
	double GetSide(int number);
	~TriangleCylinder();
};

class RingCylinder : public Cylinder
{
private:
	RingCylinder(Ring* f, double h);

public:
	static RingCylinder* CreateInstance(Ring* f, double h);
	double GetSmallRadius();
	double GetBigRadius();
	~RingCylinder();
};