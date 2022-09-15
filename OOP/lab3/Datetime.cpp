#include "Datetime.h"
#include <stdlib.h>

bool Datetime::VerificationDate(int date, int typeOfDate)
{
    switch (typeOfDate)
    {
    case 0:
        if (date >= 0 && date < 24) return true;
        else return false;
    case 1:
        if (date >= 0 && date < 60) return true;
        else return false;
    case 2:
        if (date >= 0 && date < 60) return true;
        else return false;
    case 3:
        if (date > 0 && date < 32) return true;
        else return false;
    case 4:
        if (date > 0 && date < 13) return true;
        else return false;
    case 5:
        if (date >= 1970 && date < 2038) return true;
        else return false;
    default:
        return false;
    }
}

Datetime::Datetime(int _hour, int _minute, int _second, int _day, int _month, int _year, bool& error)
{
    error = false;
    int DateArray[6] = { _hour, _minute, _second, _day, _month, _year };
    for (int i = 0; i < 6; i++)
    {
        if (!VerificationDate(DateArray[i], i)) error = true;
    }
    if (!error)
    {
        hour = _hour;
        minute = _minute;
        second = _second;
        day = _day;
        month = _month;
        year = _year;
    }
}

Datetime::Datetime()
{
    SystemDate();
}

void Datetime::Set(int date, int typeOfDate, bool& error)
{
    error = false;
    switch (typeOfDate)
    {
    case 0:
        if (VerificationDate(date, _hour_)) hour = date;
        else error = true;
        break;
    case 1:
        if (VerificationDate(date, _minute_)) minute = date;
        else error = true;
        break;
    case 2:
        if (VerificationDate(date, _second_)) second = date;
        else error = true;
        break;
    case 3:
        if (VerificationDate(date, _day_)) day = date;
        else error = true;
        break;
    case 4:
        if (VerificationDate(date, _month_)) month = date;
        else error = true;
        break;
    case 5:
        if (VerificationDate(date, _year_)) year = date;
        else error = true;
        break;
    default:
        error = true;
        break;
    }
}

int Datetime::Get(int typeOfDate)
{
    switch (typeOfDate)
    {
    case 0:
        return hour;
    case 1:
        return minute;
    case 2:
        return second;
    case 3:
        return day;
    case 4:
        return month;
    case 5:
        return year;
    default:
        return 0;
    }
}

void Datetime::SystemDate()
{
    tm timeinfo;
    time_t t;
    time(&t);
    localtime_s(&timeinfo, &t);
    hour = timeinfo.tm_hour;
    minute = timeinfo.tm_min;
    second = timeinfo.tm_sec;
    day = timeinfo.tm_mday;
    month = timeinfo.tm_mon + 1;
    year = timeinfo.tm_year + 1900;
}

time_t Datetime::GetUnixTime()
{
    tm timeinfo;
    time_t t;
    timeinfo = {
        second,
        minute,
        hour,
        day,
        month - 1,
        year - 1900
    };
    t = mktime(&timeinfo);
    return t;
}

void Datetime::GetNormalTime(time_t t)
{
    tm timeinfo;
    localtime_s(&timeinfo, &t);
    hour = timeinfo.tm_hour;
    minute = timeinfo.tm_min;
    second = timeinfo.tm_sec;
    day = timeinfo.tm_mday;
    month = timeinfo.tm_mon + 1;
    year = timeinfo.tm_year + 1900;
}

void Datetime::NextDate()
{
    int min = 2419200 * 2;
    int max = 31536000;
    GetNormalTime(GetUnixTime() + min + rand() % (max - min + 1));
}

void Datetime::PrevDate()
{
    int min = 2419200 * 2;
    int max = 31536000;
    GetNormalTime(GetUnixTime() - min - rand() % (max - min + 1));
}