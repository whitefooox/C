#include <iostream>
#include "Datetime.h"
#include "DatetimeMsecond.h"

using namespace std;

int main()
{
    Datetime datetime;
    DatetimeMsecond datetimemsecond;
    Datetime* dt = &datetimemsecond;
    dt->PrintDate();
    dt = &datetime;
    dt->PrintDate();
    return 0;
}