#include <iostream>
using namespace std;

class Date
{
private:
    int year = 1960 ;
    int month = 1 ;
    int day = 1 ;
    int hour = 0 ;
    int minute = 0 ;
    int seconds = 0 ;
    bool isOurEra = true ;

public:
    Date(int y, int m, int d, int h, int min, int sec, bool e) : year(y), month(m), day(d), hour(h), minute(min), seconds(sec), isOurEra(e)
    {
        if (!isOurEra)
            year = (year == 0) ? -1 : -year;
    }

    static bool VisYear(int year)
    {
        return (abs(year) % 4 == 0) && ((abs(year) % 100 != 0) || (abs(year) % 400 == 0));
    }

    static int DaysInMonth(int year, int month)
    {
        switch (month)
        {
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 2:
            return (VisYear(year) ? 29 : 28);
        default:
            return 31;
        }
    }

    Date operator+(const Date &data2) const
    {
        Date result = *this;
        result.seconds += data2.seconds + 60 * (result.seconds >= 60);
        result.minute += data2.minute + 60 * (result.minute >= 60);
        result.hour += data2.hour + 24 * (result.hour >= 24);
        result.day += data2.day;
        
        while (result.day > DaysInMonth(result.year, result.month))
        {
            result.day -= DaysInMonth(result.year, result.month);
            result.month++;
            if (result.month > 12)
                result.month = 1, result.year++;
        }
        
        result.month += data2.month + 12 * (result.month > 12);
        result.year += data2.year;
        result.isOurEra = (result.year >= 0);
        if (!result.isOurEra)
            result.year = -result.year;
            
        return result;
    }

    Date &operator+=(const Date &data2)
    {
        *this = *this + data2;
        return *this;
    }

    Date operator-(const Date &data2) const
    {
        Date result = *this;
        result.seconds -= data2.seconds - 60 * (result.seconds < 0);
        result.minute -= data2.minute - 60 * (result.minute < 0);
        result.hour -= data2.hour - 24 * (result.hour < 0);
        result.day -= data2.day;
        while (result.day <= 0)
        {
            if (--result.month <= 0)
                result.month += 12, result.year--;
            result.day += DaysInMonth(result.year, result.month);
        }
        result.month -= data2.month - 12 * (result.month > 12);
        result.year -= data2.year;
        result.isOurEra = (result.year >= 0);
        if (!result.isOurEra)
            result.year = -result.year;
        return result;
    }

    Date &operator-=(const Date &data2)
    {
        *this = *this - data2;
        return *this;
    }

    Date &operator= (const Date &data2)
    {
        year = data2.year;
        month = data2.month;
        day = data2.day;
        hour = data2.hour;
        minute = data2.minute;
        seconds = data2.seconds;
        isOurEra = data2.isOurEra;

        return *this;
    }

    bool operator<(const Date &data2) const
    {
        return (year, month, day, hour, minute, seconds) < (data2.year, data2.month, data2.day, data2.hour, data2.minute, data2.seconds);
    }

    bool operator>(const Date &data2) const
    {
        return  (year, month, day, hour, minute, seconds) >  (data2.year, data2.month, data2.day, data2.hour, data2.minute, data2.seconds);
    }

    bool operator==(const Date &data2) const
    {
        return  (year, month, day, hour, minute, seconds, isOurEra) ==  (data2.year, data2.month, data2.day, data2.hour, data2.minute, data2.seconds, data2.isOurEra);
    }

    friend ostream &operator<<(ostream &out, const Date &date)
    {
        out << "Year: " << date.year << ", Month: " << date.month << ", Day: " << date.day
            << " Hour: " << date.hour << ", Minute: " << date.minute << ", Seconds: " << date.seconds << (date.isOurEra ? " OurEra" : " BeforeOurEra");
        return out;
    }

    Date add(unsigned y, unsigned short m, unsigned short d,
             unsigned short h, unsigned short min, unsigned short s, bool era)
    {
        return *this + Date(y, m, d, h, min, s, era);
    }

    Date subtract(unsigned y, unsigned short m, unsigned short d,
                  unsigned short h, unsigned short min, unsigned short s, bool era)
    {
        return *this - Date(y, m, d, h, min, s, era);
    }

    Date() = default;
};

int main()
{
    Date date1(2023, 2, 29, 0, 0, 0, true);
    Date date2(8000, 0, 0, 0, 0, 0, false);

     cout << date1 + date2 <<  endl;
    
    cout << date1 - date2 << endl;
    return 0;
}