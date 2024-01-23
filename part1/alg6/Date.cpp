//
// Created by gribk on 06.04.2023.
//

#include "Date.h"

// конструктор из строки
Date::Date(string date) {
    string s = "";
    bool next_day = true;
    for (char i : date) {
        if (i == '.') {
            if (next_day) {
                day = stoi(s);
                next_day = false;
                s = "";
            } else {
                month = stoi(s);
                s = "";
            }
        } else {
            s += i;
        }
    }
    year = stoi(s);
}

// конструктор из другой даты
Date::Date(Date *date) : day(date->day), month(date->month), year(date->year) {}

// текущая больше аргумента
bool Date::this_later_second(Date *b) {
    if (year != b->year) return year > b->year;
    if (month != b->month) return month > b->month;
    if (day != b->day) return day > b->day;
    return true;
}

// преобразовать в строку
string Date::in_string() {
    return to_string(day) + "." + to_string(month) + "." + to_string(year);
}

// не равны ли
bool Date::compare(Date *b) {
    return year == b->year && month == b->month && day == b->day;
}

Date::Date(unsigned int day, unsigned int month, unsigned int year) : day(day), month(month), year(year) {}
