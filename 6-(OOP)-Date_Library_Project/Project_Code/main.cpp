#include <iostream>
#include "libs/myOwnDate.h"

using namespace std;

int main()
{

    clsDate d1("1/1/2024");
    d1.Print();// print now date
    // d1.PrintYearCalender();
    cout << d1.GetMyAgeInDays();

    return 0;
}