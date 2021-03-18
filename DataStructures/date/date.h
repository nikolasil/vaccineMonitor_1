#ifndef DATE_H
#define DATE_H

#include <string>

using namespace std;

class date
{
public:
    date(string dd, string mm, string yy);
    date(string d);
    ~date();

    void print();
    int compare(date d);
    bool isValid();

    // GETTERS
    string getDay();
    string getMonth();
    string getYear();

    // SETTERS
    void setDay(string d);
    void setMonth(string m);
    void setYear(string y);
    void setAll(string dd, string mm, string yy);
    void setAll(string d);

private:
    string day;
    string month;
    string year;
};

#endif