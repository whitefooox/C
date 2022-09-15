#pragma once
class Figure
{
public:
	virtual double Area() = 0;
	virtual double Perimeter() = 0;
	virtual Figure* Clone() = 0;
};

class Circle : public Figure
{
private:
	double r;
public:
	double Area();
	double Perimeter();
	Circle* Clone();

	Circle(double r);
};

class Triangle : public Figure
{
private:
	double a;
	double b;
	double c;
public:
	double Perimeter();
	double Area();
	Triangle* Clone();

	Triangle(double a, double b, double c);
};

class Ring : public Figure
{
private:
	double r;
	double R;
public:
	double Perimeter();
	double Area();
	Ring* Clone();

	Ring(double r, double R);
};
