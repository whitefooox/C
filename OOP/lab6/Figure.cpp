#define _USE_MATH_DEFINES
#include "Figure.h"
#include <cmath>

//______________________Circle______________________________

double Circle::CalcArea()
{
	return M_PI * r * r;
}

double Circle::CalcPerimeter()
{
	return 2 * M_PI * r;
}

double Circle::GetRadius()
{
	return r;
}

Circle::Circle(double r)
{
	if (r > 0) this->r = r;
	else this->r = 1;
}

//______________________Triangle______________________________

double Triangle::CalcArea()
{
	double p = CalcPerimeter() / 2;
	return sqrt(p * (p - a) * (p - b) * (p - c));
}

double Triangle::CalcPerimeter()
{
	return a + b + c;
}

double Triangle::GetSide(int number)
{
	switch (number)
	{
	case 1:
	{
		return a;
	}
	case 2:
	{
		return b;
	}
	case 3:
	{
		return c;
	}
	default:
		break;
	}
	return -1;
}

Triangle::Triangle(double a, double b, double c)
{
	if (a > 0 && b > 0 && c > 0 && (a + b) > c && (a + c) > b && (b + c) > a)
	{
		this->a = a;
		this->b = b;
		this->c = c;
	}
	else
	{
		this->a = 3;
		this->b = 4;
		this->c = 5;
	}
}

//______________________Ring______________________________

double Ring::CalcArea()
{
	return M_PI * R * R - M_PI * r * r;
}

double Ring::CalcPerimeter()
{
	return 2 * M_PI * r + 2 * M_PI * R;
}

double Ring::GetSmallRadius()
{
	return r;
}
double Ring::GetBigRadius()
{
	return R;
}

Ring::Ring(double r, double R)
{
	if (r > 0 && R > 0 && r != R)
	{
		if (r > R)
		{
			this->r = R;
			this->R = r;
		}
		else
		{
			this->r = r;
			this->R = R;
		}
	}
	else
	{
		this->r = 1;
		this->R = 2;
	}
}