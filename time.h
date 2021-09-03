#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED
#include <iostream>

/**With this object the dates of arrival and departure of a train are easier to use*/
class Time
{
    int hour;
    int minute;
    int year;
    int month;
    int day;
public:

    Time();
    Time(int hour, int minute,int year, int month, int day);

    int getDay();
    int getHour();
    int getMinute();
    int getMonth();
    int getYear();

};
std::ostream& operator<<(std::ostream & os,Time time);

#endif // TIME_H_INCLUDED
