//
// Created by gribk on 01.05.2023.
//

#ifndef INC_7_LIST_H
#define INC_7_LIST_H


#include "Element.h"

struct List {
    Element *elementFirst;
    Element *elementLast;

    // конструктор
    List();

    // деструктор
    ~List();

    // есть ли элементы в списке
    bool is_empty();

    // добавление элемента в конец списка
    void push_back(int value);

    // вывод списка
    void print();

    // изъятие первого элемента
    Element *get_first();
};


#endif //INC_7_LIST_H
