#pragma once
class Figure
{
public:
	virtual double CalcArea() = 0;
	virtual double CalcPerimeter() = 0;
};

class Circle : public Figure
{
private:
	double r;
public:
	double CalcArea();
	double CalcPerimeter();
	double GetRadius();

	Circle(double r);
};

class Triangle : public Figure
{
private:
	double a;
	double b;
	double c;
public:
	enum side{
		A = 1,
		B = 2,
		C = 3,
	};
	double CalcArea();
	double CalcPerimeter();
	double GetSide(int number);

	Triangle(double a, double b, double c);
};

class Ring : public Figure
{
private:
	double r;
	double R;
public:
	double CalcArea();
	double CalcPerimeter();
	double GetSmallRadius();
	double GetBigRadius();

	Ring(double r, double R);
};
