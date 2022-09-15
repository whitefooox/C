#include "Figure3D.h"
#include <iostream>

//______________________Cylinder______________________________

double Cylinder::CalcVolume()
{
	return h * f->CalcArea();
}

Cylinder::Cylinder(Figure* f, double h)
{
	this->h = h;
	this->f = f;
}

Cylinder::~Cylinder() {}

//______________________CircleCylinder______________________________

CircleCylinder* CircleCylinder::CreateInstance(Circle* f, double h)
{
	Circle* circle = new Circle(*f);
	CircleCylinder* circleCylinder = new CircleCylinder(circle, h);
	return circleCylinder;
}

double CircleCylinder::GetRadius()
{
	Circle* circle = (Circle*)f;
	return circle->GetRadius();
}

CircleCylinder::CircleCylinder(Circle* f, double h) : Cylinder(f, h) {}

CircleCylinder::~CircleCylinder()
{
	delete (Circle*)f;
}

//______________________TriangleCylinder______________________________

TriangleCylinder* TriangleCylinder::CreateInstance(Triangle* f, double h)
{
	Triangle* triangle = new Triangle(*f);
	TriangleCylinder* triangleCylinder = new TriangleCylinder(triangle, h);
	return triangleCylinder;
}

double TriangleCylinder::GetSide(int number)
{
	Triangle* triangle = (Triangle*)f;
	return triangle->GetSide(number);
}

TriangleCylinder::TriangleCylinder(Triangle* f, double h) : Cylinder(f, h) {}

TriangleCylinder::~TriangleCylinder()
{
	delete (Triangle*)f;
}

//______________________RingCylinder______________________________

RingCylinder* RingCylinder::CreateInstance(Ring* f, double h)
{
	Ring* ring = new Ring(*f);
	RingCylinder* ringCylinder = new RingCylinder(ring, h);
	return ringCylinder;
}

double RingCylinder::GetSmallRadius()
{
	Ring* ring = (Ring*)f;
	return ring->GetSmallRadius();
}

double RingCylinder::GetBigRadius()
{
	Ring* ring = (Ring*)f;
	return ring->GetBigRadius();
}

RingCylinder::RingCylinder(Ring* f, double h) : Cylinder(f, h) {}

RingCylinder::~RingCylinder()
{
	delete (Ring*)f;
}