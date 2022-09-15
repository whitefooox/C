#pragma once
#include "Datetime.h"
#include <string>
class UI
{
	public:
		void PrintMessage(std::string message);
		void PrintErrorMessage(std::string message);
		void PrintDate(Datetime date);
		void PrintTableRow(int i, Datetime date1, Datetime date2, Datetime date3);
		void PrintTableRow(int i, Datetime date1, Datetime date2);
};

