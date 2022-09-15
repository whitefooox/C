#include "Application.h"

using namespace std;

void Application::ReadDate(string fileName)
{
    bool error;
    bool error_ = false;
    int hour, minute, second, day, month, year;
    ifstream file(fileName);
    string line;
    while (getline(file, line))
    {
        dateSize++;
    }
    date = new Datetime[dateSize];
    int i = 0;
    file.clear();
    file.seekg(0, ios::beg);
    while (getline(file, line))
    {
        istringstream line_(line);
        line_ >> hour >> minute >> second >> day >> month >> year;
        date[i] = Datetime(hour, minute, second, day, month, year, error);
        if (error)
        {
            date[i] = Datetime();
            error_ = true;
        }
        i++;
    }
    if (error_)
    {
        ui.PrintErrorMessage("\nIncorrect data! The current time will be used instead.\n");
    }
    file.close();
}

Application::Application()
{
    date = NULL;
    prev = NULL;
    dateSize = 0;
}

Application::~Application()
{
    delete[] date;
    delete[] prev;
}

void Application::Main()
{
    Datetime dateNext, datePrev;
    prev = new Datetime[dateSize];
    ui.PrintMessage("\n\tRead data:\n");
    for (int i = 0; i < dateSize; i++)
    {
        dateNext = date[i];
        datePrev = date[i];
        dateNext.NextDate();
        datePrev.PrevDate();
        ui.PrintTableRow(i + 1, date[i], dateNext, datePrev);
        prev[i] = datePrev;
    }
    ui.PrintMessage("\n\nTask of variant 8:\n\n");
    for(int i = 0; i < dateSize; i++)
    {
        if (date[i].Get(_year_) == prev[i].Get(_year_))
        {
            ui.PrintTableRow(i + 1, date[i], prev[i]);
        }
    }
}

void Application::SystemDate()
{
    Datetime dateTemp;
    dateTemp.SystemDate();
    ui.PrintMessage("\t\nSystem time:");
    ui.PrintDate(dateTemp);
}