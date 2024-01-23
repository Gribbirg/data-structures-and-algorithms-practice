//
// Created by gribk on 01.05.2023.
//

#ifndef INC_7_ELEMENT_H
#define INC_7_ELEMENT_H

#include <iostream>

using namespace std;


struct Element {

    // значение элемента
    int value;

    // указатель на следующий элемент
    Element *nextElement;

    // конструктор
    Element(int value);
};


#endif //INC_7_ELEMENT_H
