#define _USE_MATH_DEFINES
#include "Figure.h"
#include <cmath>

Circle::Circle(double _r)
{
	if (_r > 0) r = _r;
	else r = 1;
}

double Circle::Area()
{
	return M_PI * r * r;
}

double Circle::Perimeter()
{
	return 2 * M_PI * r;
}

Circle* Circle::Clone()
{
	return new Circle(*this);
}

double Triangle::Perimeter()
{
	return a + b + c;
}

double Triangle::Area()
{
	double p = Perimeter() / 2;
	return sqrt(p * (p - a) * (p - b) * (p - c));
}

Triangle::Triangle(double A, double B, double C)
{
	if (A > 0 && B > 0 && C > 0 && (A + B) > C && (A + C) > B && (B + C) > A)
	{
		a = A;
		b = B;
		c = C;
	}
	else
	{
		a = 3;
		b = 4;
		c = 5;
	}
}

Triangle* Triangle::Clone()
{
	return new Triangle(*this);
}

double Ring::Perimeter()
{
	return 2 * M_PI * r + 2 * M_PI * R;
}

double Ring::Area()
{
	return M_PI * R * R - M_PI * r * r;
}

Ring* Ring::Clone()
{
	return new Ring(*this);
}

Ring::Ring(double r1, double r2)
{
	if (r1 > 0 && r2 > 0 && r1 != r2)
	{
		if (r1 > r2)
		{
			r = r2;
			R = r1;
		}
		else
		{
			r = r1;
			R = r2;
		}
	}
	else
	{
		r = 1;
		R = 2;
	}
}