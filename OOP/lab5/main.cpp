#include <iostream>
#include "Figure3D.h"

using namespace std;

int main()
{
	int select;
	Figure* F = NULL;
	cout << "Select a figure: (1 - Circle, 2 - Triangle, 3 - Ring): "; cin >> select;
	switch (select)
	{
	case 1:
	{
		double r;
		cout << "Enter the radius:\n"; 
		cout << "r = "; cin >> r;
		F = new Circle(r);
		break;
	}
	case 2:
	{
		double a, b, c;
		cout << "Enter the sides of the triangle:\n";
		cout << "a = "; cin >> a;
		cout << "b = "; cin >> b;
		cout << "c = "; cin >> c;
		F = new Triangle(a, b, c);
		break;
	}
	case 3:
	{
		double r1, r2;
		cout << "Enter the ring radii:\n";
		cout << "r1 = "; cin >> r1;
		cout << "r2 = "; cin >> r2;
		F = new Ring(r1, r2);
		break;
	}
	default:
		delete F;
		return 0;
		break;
	}
	cout << "Enter the height of the cylinder:\n";
	int h;
	cout << "h = "; cin >> h;
	Cylinder C(F, h);
	cout << "The resulting volume of the figure:\n";
	cout << C.Volume();
	delete F;
}