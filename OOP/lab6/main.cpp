#include <iostream>
#include "Figure3D.h"

using namespace std;

int main()
{
	Cylinder* X = NULL;
	int select;
	cout << "Enter the height of the cylinder:\n";
	int h;
	cout << "h = "; cin >> h;
	cout << "Select a figure: (1 - Circle, 2 - Triangle, 3 - Ring): "; cin >> select;
	switch (select)
	{
	case 1:
	{
		double r;
		cout << "Enter the radius:\n";
		cout << "r = "; cin >> r;
		Circle* c = new Circle(r);
		X = CircleCylinder::CreateInstance(c, h);
		delete c;
		break;
	}
	case 2:
	{
		double a, b, c;
		cout << "Enter the sides of the triangle:\n";
		cout << "a = "; cin >> a;
		cout << "b = "; cin >> b;
		cout << "c = "; cin >> c;
		Triangle* t = new Triangle(a, b, c);
		X = TriangleCylinder::CreateInstance(t, h);
		delete t;
		break;
	}
	case 3:
	{
		double r1, r2;
		cout << "Enter the ring radii:\n";
		cout << "r1 = "; cin >> r1;
		cout << "r2 = "; cin >> r2;
		Ring* r = new Ring(r1, r2);
		X = RingCylinder::CreateInstance(r, h);
		delete r;
		break;
	}
	default:
		return 0;
		break;
	}
	cout << "The resulting volume of the figure:\n";
	cout << X->CalcVolume();
	delete X;
}