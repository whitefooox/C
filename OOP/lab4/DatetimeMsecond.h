#pragma once
#include "Datetime.h"

enum {
    _millisecond_ = 6
};

class DatetimeMsecond : public Datetime
{
public:
    int millisecond;

    void Set(int data, int typeOfDate, bool& error);
    int Get(int typeOfDate);
    void SystemDate();

    void PrintDate();

    DatetimeMsecond();

    DatetimeMsecond(int _millisecond, int _hour, int _minute, int _second, int _day, int _month, int _year, bool& error);

private:
    bool VerificationDateMsecond(int date);
};

