#include <iostream>
#include "Figure3D.h"
#include "Exception.h"

using namespace std;
int main()
{
	double r, h;
	bool check = true;
	Cylinder<Circle>* cylinder = NULL;
	while (check)
	{
		cout << "Enter the radius and height: " << endl;
		cout << "r = "; cin >> r;
		cout << "h = "; cin >> h;
		try
		{
			Circle* circle = new Circle(r);
			try
			{
				cylinder = new Cylinder<Circle>(circle, h);
				delete circle;
				check = false;
			}
			catch (Exception& error)
			{
				delete circle;
				throw error;
				cout << "Try again..." << endl << endl;
			}
		}
		catch (Exception& error)
		{
			error.Show();
			cout << "Try again..." << endl << endl;
		}
	}
	cout << cylinder->CalcVolume();
	delete cylinder;
}