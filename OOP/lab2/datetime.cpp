#include <iostream>
#include <time.h>
#include "datetime.h"

void Datetime::Set(int data, int type_of_date)
{
    switch (type_of_date)
    {
    case 0:
        hour = data;
        break;
    case 1:
        minute = data;
    case 2:
        second = data;
    case 3:
        day = data;
    case 4:
        month = data;
    case 5:
        year = data;
    default:
        break;
    }
}

int Datetime::Get(int type_of_date)
{
    switch (type_of_date)
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

void Datetime::SystemTime(Datetime& system)
{
    time_t rawtime;
    tm timeinfo;
    time(&rawtime);
    localtime_s(&timeinfo, &rawtime);
    system.hour = timeinfo.tm_hour;
    system.minute = timeinfo.tm_min;
    system.second = timeinfo.tm_sec;
    system.day = timeinfo.tm_mday;
    system.month = timeinfo.tm_mon + 1;
    system.year = timeinfo.tm_year + 1900;
}

void Datetime::GetNextDate(Datetime& next)
{
    int min = 2419200 * 2;
    int max = 31536000;
    GetNormalTime(GetUnixTime(*this) + (min + rand() % (max - min + 1)), next);
}

void Datetime::GetPrevDate(Datetime& prev)
{
    int min = 2419200 * 2;
    int max = 31536000;
    GetNormalTime(GetUnixTime(*this) - (min + rand() % (max - min + 1)), prev);
}

time_t GetUnixTime(Datetime A)
{
    tm timeinfo;
    timeinfo.tm_year = A.Get(_year_) - 1900;
    timeinfo.tm_mon = A.Get(_month_) - 1;
    timeinfo.tm_mday = A.Get(_day_);
    timeinfo.tm_hour = A.Get(_hour_);
    timeinfo.tm_min = A.Get(_minute_);
    timeinfo.tm_sec = A.Get(_second_);
    time_t unix_time = mktime(&timeinfo);
    return unix_time;
}

void GetNormalTime(time_t unix_time, Datetime& A)
{
    tm timeinfo;
    localtime_s(&timeinfo, &unix_time);
    A.Set(timeinfo.tm_hour, _hour_);
    A.Set(timeinfo.tm_min, _minute_);
    A.Set(timeinfo.tm_sec, _second_);
    A.Set(timeinfo.tm_mday, _day_);
    A.Set(timeinfo.tm_mon + 1, _month_);
    A.Set(timeinfo.tm_year + 1900, _year_);
}

void Datetime::Output()
{
    printf("%i:%i:%i %i/%i/%i", hour, minute, second, day, month, year);
}