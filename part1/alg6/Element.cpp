//
// Created by gribk on 06.04.2023.
//

#include "Element.h"

// конструктор
Element::Element(string id, Date *date, double value, bool back) :
        id(id),
        date(date),
        value(value),
        back(back),
        next(nullptr),
        previous(nullptr) {}

// деструктор
Element::~Element() {
    delete date;
}