//
// Created by gribk on 06.04.2023.
//

#ifndef INC_6_LIST_H
#define INC_6_LIST_H


#include "Element.h"
#include <ctime>

struct List {
    Element *first;
    Element *last;

    List();
    ~List();

    bool is_empty();
    void push_back(string id, Date *date, double value, bool back);
    void push_front(string id, Date *date, double value, bool back);
    string bool_to_string(bool a);
    void print_left_to_right();
    void print_right_to_left();
    void remove_element(string id, Date *date);
    Element *find_element(string id);
    void swap(Element *element_first, Element *element_second);
    void sort_by_date();
    void remove_element_by_num(int num);
    List *create_new_with_back();
    void push_back_random(int i);
};


#endif //INC_6_LIST_H
