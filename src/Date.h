#ifndef DATE_H
#define DATE_H

#include "includes.h"

bool validate_cin();

class Date{
public:
    int month;
    int day;
    int year;

    int hour;
    int minute;
    bool AM; //true for AM, false for PM

    Date();
    Date(int mon,int d,int y, int h, int min, bool AM_PM);
    Date(const Date&);

    bool checkDate() const;
    Date& operator = (const Date& temp);
    void createDate();
    void display() const;

    bool operator >  (const Date&);
    bool operator >= (const Date&);
    bool operator == (const Date&);
    bool operator <= (const Date&);
    bool operator <  (const Date&);
};

#endif