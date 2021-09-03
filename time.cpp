#include "time.h"
#include <iomanip>

Time::Time():hour(0),minute(0),year(0),month(0),day(0) {}
Time::Time(int hour, int minute,int year, int month, int day):hour(hour), minute(minute),year(year),month(month),day(day) {}

int Time::getDay()
{
    return day;
}
int Time::getHour()
{
    return hour;
}
int Time::getMinute()
{
    return minute;
}
int Time::getMonth()
{
    return month;
}
int Time::getYear()
{
    return year;
}

std::ostream& operator<<(std::ostream & os,Time time)
{
    os<<time.getYear()<<std::setw(3)<<"\\"<<std::setw(2)<<time.getMonth()<<"\\"<<std::setw(2)<<time.getDay()<<" "<<std::setw(2)<<time.getHour()<<":"<<std::setw(2)<<time.getMinute() ;
    return os;
}
