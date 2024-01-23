//
// Created by gribk on 06.04.2023.
//

#ifndef INC_6_DATE_H
#define INC_6_DATE_H
#include <string>
#include <iostream>

using namespace std;

struct Date {
    unsigned int day;
    unsigned int month;
    unsigned int year;

    Date(string date);
    Date(Date *date);

    Date(unsigned int day, unsigned int month, unsigned int year);

    bool this_later_second(Date *b);
    bool compare(Date *b);
    string in_string();
};


#endif //INC_6_DATE_H
