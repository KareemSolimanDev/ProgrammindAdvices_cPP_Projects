#include <iostream>
#include <time.h>

using namespace std;

class clsDate
{
private:
    unsigned short _Day;
    unsigned short _Month;
    unsigned short _Year;

public:
    clsDate()
    {
        time_t t = time(0);
        tm *now = localtime(&t);
        _Day = now->tm_mday;
        _Month = now->tm_mon + 1;
        _Year = now->tm_year + 1900;
    }
    clsDate(unsigned short day, unsigned short month, unsigned short year)
    {
        _Day = day;
        _Month = month;
        _Year = year;
    }
    clsDate(unsigned short dayOrder, unsigned short year)
    {
        clsDate date = GetDateFromDayOrderInYear(dayOrder, year);
        _Day = date.getDay();
        _Month = date.getMonth();
        _Year = date.getYear();
    }
    clsDate(string Date)
    {
        clsDate date = SplitDate(Date);
        _Day = date.getDay();
        _Month = date.getMonth();
        _Year = date.getYear();
    }
    unsigned short getDay() { return _Day; }
    unsigned short getMonth() { return _Month; }
    unsigned short getYear() { return _Year; }
    void setDay(unsigned short day) { _Day = day; }
    void setMonth(unsigned short month) { _Month = month; }
    void setYear(unsigned short year) { _Year = year; }

    static bool IsLeap(short yearNum)
    {
        return (yearNum % 400 == 0) || (yearNum % 4 == 0 && yearNum % 100 != 0);
    }
    static string FormatDate(clsDate Date, char delim = '/')
    {
        return to_string(Date.getDay()) + delim + to_string(Date.getMonth()) + delim + to_string(Date.getYear());
    }
    static short GetMonthDays(short month, short year)
    {
        short arrDaysinMonthes[12] = {31, short(28 + IsLeap(year)), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        return arrDaysinMonthes[month - 1];
    }
    static clsDate GetDateFromDayOrderInYear(short dayOrder, short Year)
    {
        clsDate date;
        short restdays = dayOrder;
        short month;
        for (month = 0; restdays > GetMonthDays(month, Year); month++)
        {
            restdays -= GetMonthDays(month, Year);
        }
        date.setDay(restdays);
        date.setMonth(month);
        date.setYear(Year);
        return date;
    }
    static clsDate SplitDate(string Date, char delim = '/')
    {
        unsigned short arrDateElements[3];
        short counter = 0;
        string num = "";
        for (char i : Date + delim)
        {
            if (i == delim)
            {
                arrDateElements[counter] = stoi(num);
                counter++;
                num = "";
            }
            else
            {
                num += i;
            }
        }
        return {arrDateElements[0], arrDateElements[1], arrDateElements[2]};
    }
    static short DayOrderInWeek(short Day, short Month, short Year)
    {
        short a, y, m;
        a = (14 - Month) / 12;
        y = Year - a;
        m = Month + (12 * a) - 2; // 0:sun, 1:Mon, 2:Tue ...etc
        return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }
    static string DayShortName(short dayOrder)
    {
        string arrDayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
        return arrDayNames[dayOrder];
    }
    static string MonthShortName(short month)
    {
        string months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        return months[month - 1];
    }
    static short GetDayOrderInYear(short day, short month, short year)
    {
        short sumOfDays = day;
        for (size_t i = 0; i < month - 1; i++)
        {
            sumOfDays += GetMonthDays(i, year);
        }
        return sumOfDays;
    }
    static clsDate GetDateAfterNDay(short Day, short Month, short Year, short afterDays)
    {
        return GetDateFromDayOrderInYear(GetDayOrderInYear(Day, Month, Year) + afterDays, Year);
    }
    static bool IsFirstDateOlder(clsDate FstDate, clsDate SecDate)
    {
        return FstDate.getYear() < SecDate.getYear()
                   ? true
                   : (FstDate.getYear() == SecDate.getYear()
                          ? (FstDate.getMonth() < SecDate.getMonth()
                                 ? true
                                 : (FstDate.getMonth() == SecDate.getMonth()
                                        ? FstDate.getDay() < SecDate.getDay()
                                        : false))
                          : false);
    }
    static bool IsDatesEquals(clsDate FstDate, clsDate SecDate)
    {

        return FstDate.getYear() == SecDate.getYear() && FstDate.getMonth() == SecDate.getMonth() && FstDate.getDay() == SecDate.getDay();
    }
    static clsDate IncreaseDateByXDay(clsDate date, short days)
    {
        return GetDateFromDayOrderInYear(GetDayOrderInYear(date.getDay(), date.getMonth(), date.getYear()) + days, date.getYear());
    }
    static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
    {
        int Days = 0;
        while (IsFirstDateOlder(Date1, Date2))
        {
            Days++;
            Date1 = IncreaseDateByXDay(Date1, 1);
        }
        return IncludeEndDay ? ++Days : Days;
    }

    bool IsLeap()
    {
        return IsLeap(_Year);
    }
    string FormatDate()
    {
        return FormatDate(*this);
    }
    short GetMonthDays()
    {
        return GetMonthDays(_Month, _Year);
    }
    void PrintYearData()
    {
        // is leap year function return true as 1
        short days = 365 + IsLeap(_Year);
        unsigned short hours = days * 24;
        unsigned int minutes = hours * 60;
        unsigned int secounds = minutes * 60;
        cout << "=========================================================\n";
        cout << "Monthes in this Year [" << _Year << "] is :" << 12 << "\n";
        cout << "Days in this Year [" << _Year << "] is :" << days << "\n";
        cout << "Hours in this Year [" << _Year << "] is :" << hours << "\n";
        cout << "Minutes in this Year [" << _Year << "] is :" << minutes << "\n";
        cout << "Secounds in this Year [" << _Year << "] is :" << secounds << "\n";
        cout << "=========================================================" << endl;
    }
    void PrintMonthData()
    {
        short days = this->GetMonthDays();
        unsigned short hours = days * 24;
        unsigned int minutes = hours * 60;
        unsigned int secounds = minutes * 60;

        cout << "=========================================================\n";
        cout << "Days in [" << _Year << "/" << _Month << "] is :" << days << "\n";
        cout << "Hours in [" << _Year << "/" << _Month << "] is :" << hours << "\n";
        cout << "Minutes in [" << _Year << "/" << _Month << "] is :" << minutes << "\n";
        cout << "Secounds in [" << _Year << "/" << _Month << "] is :" << secounds << "\n";
        cout << "=========================================================" << endl;
    }
    short DayOrderInWeek()
    {
        return DayOrderInWeek(_Day, _Month, _Year);
    }
    string DayShortName()
    {
        return DayShortName(this->DayOrderInWeek());
    }
    string MonthShortName()
    {
        return MonthShortName(_Month);
    }
    void PrintMonthCalender(short month)
    {
        short current = DayOrderInWeek(1, month, _Year);

        // print header
        cout << "===============| " << MonthShortName(month) << " |===============\n\n";
        for (size_t i = 0; i < 7; i++)
        {
            cout << DayShortName(i) << "  ";
        }
        cout << '\n';

        // fill unwanted days
        for (size_t i = 0; i < current; i++)
        {
            cout << "     "; // three spaces for short name of day and two spaces for the gap between names in header
        }
        // print days
        for (size_t i = 1; i <= this->GetMonthDays(); i++)
        {
            cout << " " << i << ((i >= 10) ? "  " : "   ");

            if (++current == 7)
            {
                current = 0;
                cout << '\n';
            }
        }
        cout << "\n=====================================" << endl;
    }
    void PrintMonthCalender()
    {
        short current = DayOrderInWeek(1, _Month, _Year);

        // print header
        cout << "===============| " << MonthShortName() << " |===============\n\n";
        for (size_t i = 0; i < 7; i++)
        {
            cout << DayShortName(i) << "  ";
        }
        cout << '\n';

        // fill unwanted days
        for (size_t i = 0; i < current; i++)
        {
            cout << "     "; // three spaces for short name of day and two spaces for the gap between names in header
        }
        // print days
        for (size_t i = 1; i <= this->GetMonthDays(); i++)
        {
            cout << " " << i << ((i >= 10) ? "  " : "   ");

            if (++current == 7)
            {
                current = 0;
                cout << '\n';
            }
        }
        cout << "\n=====================================" << endl;
    }
    void PrintYearCalender()
    {
        cout << "=====================================\n";
        cout << "\tCalender : " << _Year << '\n';
        cout << "=====================================" << endl;
        for (size_t i = 1; i <= 12; i++)
        {
            PrintMonthCalender(i);
        }
    }
    short GetDayOrderInYear()
    {
        return GetDayOrderInYear(_Day, _Month, _Year);
    }
    bool IsLastMonth()
    {
        return _Month == 12;
    }
    bool IsLastDay()
    {
        return _Day == GetMonthDays();
    }
    clsDate GetTomorrowDate()
    {
        return IncreaseDateByXDay(*this, 1);
    }
    unsigned int GetMyAgeInDays()
    {
        time_t now = time(0);
        struct tm *lt = localtime(&now);
        clsDate nowDate(lt->tm_mday, lt->tm_mon + 1, lt->tm_year + 1900);
        return GetDifferenceInDays(*this, nowDate, true);
    }
    bool IsValid()
    {
        return ((_Year > 0 && _Year <= 3000) && (_Month <= 12 && _Month > 0) && (_Day <= GetMonthDays(_Month, _Year) && _Day > 0));
    }

    void Print()
    {
        cout << FormatDate(*this) << endl;
    }
};