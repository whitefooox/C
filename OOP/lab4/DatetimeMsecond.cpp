#include "DatetimeMsecond.h"
#include <iostream>
#include <windows.h>

DatetimeMsecond::DatetimeMsecond() : Datetime() {
    SYSTEMTIME st;
    GetLocalTime(&st);
    millisecond = st.wMilliseconds;
};

DatetimeMsecond::DatetimeMsecond(int _millisecond, int _hour, int _minute, int _second, int _day, int _month, int _year, bool& error) :
    Datetime(_hour, _minute, _second, _day, _month, _year, error) {
    millisecond = _millisecond;
};

bool DatetimeMsecond::VerificationDateMsecond(int date)
{
    if (date >= 0 && date < 1000)
    {
        return true;
    }
    else return false;
}

void DatetimeMsecond::Set(int date, int typeOfDate, bool& error)
{
    error = false;
    if (typeOfDate == 6)
    {
        if (VerificationDateMsecond(date)) millisecond = date;
        else error = true;
    }
    else
    {
        Datetime::Set(date, typeOfDate, error);
    }
}

void DatetimeMsecond::SystemDate()
{
    Datetime::SystemDate();
    SYSTEMTIME st;
    GetLocalTime(&st);
    millisecond = st.wMilliseconds;
}

int DatetimeMsecond::Get(int typeOfDate)
{
    if (typeOfDate == 6)
    {
        return millisecond;
    }
    else
    {
        Datetime::Get(typeOfDate);
    }
}

void DatetimeMsecond::PrintDate()
{
    printf("%i:%i:%i:%i %i/%i/%i\n", Get(_hour_), Get(_minute_), Get(_second_), millisecond, Get(_day_), Get(_month_), Get(_year_));
}