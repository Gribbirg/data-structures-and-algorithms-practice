//
// Created by gribk on 06.04.2023.
//

#ifndef INC_6_ELEMENT_H
#define INC_6_ELEMENT_H


#include "Date.h"

struct Element {
    string id;
    Date *date;
    double value;
    bool back;

    Element *next;
    Element *previous;

    Element(string id, Date *date, double value, bool back);
    ~Element();
};


#endif //INC_6_ELEMENT_H
