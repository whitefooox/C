#include "UI.h"
#include <iostream>

void UI::PrintDate(Datetime date)
{
    printf("\t%i:%i:%i %i/%i/%i", date.Get(_hour_), date.Get(_minute_), date.Get(_second_), date.Get(_day_), date.Get(_month_), date.Get(_year_));
}

void UI::PrintTableRow(int i, Datetime date1, Datetime date2, Datetime date3)
{
    printf("\x1b[36m%i) \x1b[0m", i);
    PrintDate(date1);
    printf("\t");
    PrintDate(date2);
    printf("\t");
    PrintDate(date3);
    printf("\n");
}

void UI::PrintTableRow(int i, Datetime date1, Datetime date2)
{
    printf("\x1b[32m%i) \x1b[0m", i);
    PrintDate(date1);
    printf("\t");
    PrintDate(date2);
    printf("\n");
}

void UI::PrintMessage(std::string message)
{
    printf("\x1b[33m%s\x1b[0m", message.c_str());
}

void UI::PrintErrorMessage(std::string message)
{
    printf("\x1b[31m%s\x1b[0m", message.c_str());
}