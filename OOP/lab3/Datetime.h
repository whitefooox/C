#pragma once
#include <time.h>
enum {
    _hour_,
    _minute_,
    _second_,
    _day_,
    _month_,
    _year_
};

class Datetime
{
    private:
        int hour;
        int minute;
        int second;
        int day;
        int month;
        int year;

        bool VerificationDate(int date, int typeOfDate);
        time_t GetUnixTime();
        void GetNormalTime(time_t t);

    public:
        void SystemDate();
        void NextDate();
        void PrevDate();
        void Set(int data, int typeOfDate, bool& error);
        int Get(int typeOfDate);

    Datetime(int _hour, int _minute, int _second, int _day, int _month, int _year, bool& error);
    Datetime();
};

