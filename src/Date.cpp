#include "Date.h"
using namespace std;

Date::Date(){
    month = day = year = hour = minute = AM = 0;
}

Date::Date(int mon,int d,int y, int h, int min, bool am){
    month  = mon;
    day    =   d;
    year   =   y;
    hour   =   h;
    minute = min;
    AM     =  am;
}

Date::Date(const Date& temp){
    month  =  temp.month;
    day    =    temp.day;
    year   =   temp.year;
    hour   =   temp.hour;
    minute = temp.minute;
    AM     =     temp.AM;
}

bool Date::checkDate() const{
    if(month < 1  ||  month > 12) return false;
    
    switch(month){
        case 1:
            if(day < 1  ||  day > 31){
                return false;
            }break;
        case 2:
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                if(day < 1  ||  day > 29) return false;
            }else {
                if(day < 1  ||  day > 28) return false;
            }
            break;
        case 3:
            if(day < 1  ||  day > 31){
                return false;
            }break;
        case 4:
            if(day < 1  ||  day > 30){
                return false;
            }break;
        case 5:
            if(day < 1  ||  day > 31){
                return false;
            }break;
        case 6:
            if(day < 1  ||  day > 30){
                return false;
            }break;
        case 7:
            if(day < 1  ||  day > 31){
                return false;
            }break;
        case 8:
            if(day < 1  ||  day > 31){
                return false;
            }break;
        case 9:
            if(day < 1  ||  day > 30){
                return false;
            }break;
        case 10:
            if(day < 1  ||  day > 31){
                return false;
            }break;
        case 11:
            if(day < 1  ||  day > 30){
                return false;
            }break;
        case 12:
            if(day < 1  ||  day > 31){
                return false;
            }break;
    }

    if(hour < 1  ||  hour > 12) return false;
    
    if(minute < 0  ||  minute > 59) return false;

    return true;
}

Date& Date::operator = (const Date& temp){
    if(this != &temp){
        month  =  temp.month;
        day    =    temp.day;
        year   =   temp.year;
        hour   =   temp.hour;
        minute = temp.minute;
        AM     =     temp.AM;
    }
    return *this;
}

bool validate_cin(){
    if(cin.fail()){
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}

void Date::createDate(){
    int mon,d,y,h,min;
    do{
        cout << "Enter date input as INTEGERS" << endl;
        cout << "Enter month (1-12): ";
        cin >> mon;
        if(!validate_cin()){
            cerr << "\nInvalid input. Integer input is only accepted\n\n";
            continue;
        }

        cout << "Enter day: ";
        cin >> d;
        if(!validate_cin()){
            cerr << "\nInvalid input. Integer input is only accepted\n\n";
            continue;
        }

        cout << "Enter year: ";
        cin >> y;
        if(!validate_cin()){
            cerr << "\nInvalid input. Integer input is only accepted\n\n";
            continue;
        }
        int digits = 0;
        for(int i = y;i>0;i/=10){
            ++digits;
        }
        if(y>0 && (digits == 2 || digits == 1)) y += 2000;

        cout << "Enter hour: ";
        cin >> h;
        if(!validate_cin()){
            cerr << "\nInvalid input. Integer input is only accepted\n\n";
            continue;
        }
        cout << "Enter minute: ";
        cin >> min;
        if(!validate_cin()){
            cerr << "\nInvalid input. Integer input is only accepted\n\n";
            continue;
        }

        string input;
        do{
            cout << "Enter \"AM\" or \"PM\": ";
            cin >> input;
            if(input != "AM"  &&  input != "PM"){
                cout << "Invalid AM/PM" << endl;
            }else break;
        }while(true);

        bool AM_PM = (input == "AM") ? true : false;

        Date temp(mon,d,y,h,min,AM_PM);
        if(temp.checkDate()){
            *this = temp;
            break;
        }else{
            cout << "\nInvalid date. Please check date and try again\n\n";
        }
    }while(true);
}

void Date::display() const{
    cout << month << '/' << day << '/' << year << ", ";
    cout << hour << ':';
    if(minute / 10 == 0){
        cout << '0';
    }
    cout << minute;
    cout << (AM ? "AM" : "PM");
}

bool Date::operator > (const Date& other){
    if(year > other.year) return true;
    else if(year == other.year){
        if(month > other.month) return true;
        else if(month == other.month){
            if(day > other.day) return true;
            else if(day == other.day){
                if(AM == other.AM){
                    if(hour > other.hour) return true;
                    else if(hour == other.hour){
                        if(minute > other.minute) return true;
                        else return false;
                    }
                    else return false;
                }else if(AM && !other.AM) return false;
                else return true;
            }
            else return false;
        }
        else return false;
    }
    else return false;
}

bool Date::operator == (const Date& other){
    if(month != other.month)return false;
    if(day != other.day)return false;
    if(year != other.year)return false;
    if(hour != other.hour)return false;
    if(minute != other.minute)return false;
    if(AM != other.AM)return false;
    return true;
}

bool Date::operator >= (const Date& other){
    if(*this > other  ||  *this == other) return true;
    return false;
}

bool Date::operator < (const Date& other){
    if(*this >= other) return false;
    return true;
}

bool Date::operator <= (const Date& other){
    if(*this < other  ||  *this == other) return true;
    return false;
}