//
// Created by gribk on 01.05.2023.
//

#include "List.h"

// конструктор
List::List() : elementFirst(nullptr), elementLast(nullptr) {}

// деструктор
List::~List() {

    // если ничего нет, то и делать ничего не надо
    if (is_empty()) {
        return;
    }

    // указатели на текущий и следующий элементы
    Element *element = elementFirst;
    Element *elementNext = elementFirst->nextElement;

    // пока есть элементы
    while (elementNext) {
        // удаление текущего
        delete element;
        // следующий становится текущим
        element = elementNext;
        // чтение следующего
        elementNext = element->nextElement;
    }
    // удаление текущего
    delete element;
}

// есть ли элементы в списке
bool List::is_empty() {
    return elementFirst == nullptr;
}

// добавление элемента в конец списка
void List::push_back(int value) {

    // создание нового элемента
    Element *elementNew = new Element(value);

    // если нет элементов
    if (is_empty()) {
        // новый элемент первый и последний
        elementFirst = elementLast = elementNew;
    } else {
        // добавление в последний элемент ссылки на новый
        elementLast->nextElement = elementNew;
        // теперь новый элемент последний
        elementLast = elementNew;
    }
}

// вывод списка
void List::print() {

    // если ничего нет, то и делать ничего не надо
    if (is_empty())
        return;

    // проход по списку
    Element *element = elementFirst;
    while (element) {
        // вывод значения элемента
        cout << element->value << " ";
        element = element->nextElement;
    }
    // конец строки
    cout << endl;
}

// изъятие первого элемента
Element *List::get_first() {
    Element *element = elementFirst;

    elementFirst = element->nextElement;
    if (element == elementLast) elementFirst = nullptr;

    return element;
}