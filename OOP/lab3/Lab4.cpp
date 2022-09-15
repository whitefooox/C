#include <iostream>
#include "Application.h"
int main()
{
	srand(time(0));
	Application A;
	A.ReadDate("data.txt");
	A.SystemDate();
	A.Main();
}