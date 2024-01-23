//
// Created by gribk on 06.04.2023.
//

#include "List.h"

// конструктор
List::List() : first(nullptr), last(nullptr) {}

// деструктор
List::~List() {

    // если ничего нет, то и делать ничего не надо
    if (is_empty()) {
        return;
    }

    // указатели на текущий и следующий элементы
    Element *element = first;
    Element *elementNext = first->next;

    // пока есть элементы
    while (elementNext) {
        // удаление текущего
        delete element;
        // следующий становится текущим
        element = elementNext;
        // чтение следующего
        elementNext = element->next;
    }
    // удаление текущего
    delete element;
}

// проверка на пустоту
bool List::is_empty() {
    return first == nullptr;
}

// добавить в конец
void List::push_back(string id, Date *date, double value, bool back) {

    // создание нового элемента
    Element *elementNew = new Element(id, date, value, back);

    // если нет элементов
    if (is_empty()) {
        // новый элемент первый и последний
        first = last = elementNew;
    } else {
        // добавление в последний элемент ссылки на новый
        last->next = elementNew;
        elementNew->previous = last;
        // теперь новый элемент последний
        last = elementNew;
    }
}

// добавить в начало
void List::push_front(string id, Date *date, double value, bool back) {

    // создание нового элемента
    Element *elementNew = new Element(id, date, value, back);

    // если нет элементов
    if (is_empty()) {
        // новый элемент первый и последний
        first = last = elementNew;
    } else {
        // добавление в последний элемент ссылки на новый
        first->previous = elementNew;
        elementNew->next = first;
        // теперь новый элемент последний
        first = elementNew;
    }
}

// для красивого вывода
string List::bool_to_string(bool a) {
    return a? "Yes": "No";
}

// вывод слева направо
void List::print_left_to_right() {

    // если ничего нет, то и делать ничего не надо
    if (is_empty())
        return;

    // проход по списку
    Element *element = first;
    while (element) {
        // вывод значения элемента
        cout << "Id: " << element->id << " "
             << "Date: " << element->date->in_string() << " "
             << "Value: " << element->value << " "
             << "Back: " << bool_to_string(element->back) << endl;
        element = element->next;
    }
}

// вывод справа налево
void List::print_right_to_left() {

    // если ничего нет, то и делать ничего не надо
    if (is_empty())
        return;

    // проход по списку
    Element *element = last;
    while (element) {
        // вывод значения элемента
        cout << "Id: " << element->id << " "
             << "Date: " << element->date->in_string() << " "
             << "Value: " << element->value << " "
             << "Back: " << bool_to_string(element->back) << endl;
        element = element->previous;
    }
}

// удалить все элементы по значениям
void List::remove_element(string id, Date *date) {

    // если ничего нет, то и делать ничего не надо
    if (is_empty())
        return;

    // нужно удалить первый элемент
    while (first->id == id && first->date->compare(date)) {
        // в списке один элемент
        if (first == last) {
            // удаление первого
            delete first;
            // направление указателей в никуда
            first = last = nullptr;
            return;
        }
        // удаление первого
        first = first->next;
        delete first->previous;
        first->previous = nullptr;
    }

    Element *element = first->next;
    Element *element_next;

    // пока есть элементы
    while (element->next) {
        // текущий нежно удалить
        if (element->id == id && element->date->compare(date)) {
            element_next = element->next;
            element->previous->next = element->next;
            element->next->previous = element->previous;
            delete element;
            element = element_next;
        } else {
            element = element->next;
        }
    }
    // последний нужно удалить
    if (element->id == id && element->date->compare(date)) {
        element->previous->next = nullptr;
        last = element->previous;
        delete element;
    }
    delete date;
}

// найти элемент по id
Element* List::find_element(string id) {
    Element *element = first;
    // проход по элементам
    while (element) {
        if (element->id == id) {
            return element;
        }
        element = element->next;
    }
    cout << id << " does not exist!" << endl;
    return nullptr;
}

// заменить элементы
void List::swap(Element *element_first, Element *element_second) {
    // копии
    Element* copy = new Element(element_first->id, element_first->date, element_first->value, element_first->back);

    element_first->id = element_second->id;
    element_first->date = element_second->date;
    element_first->value = element_second->value;
    element_first->back = element_second->back;

    element_second->id = copy->id;
    element_second->date = new Date(copy->date);
    element_second->value = copy->value;
    element_second->back = copy->back;
}

// отсортировать по дате
// сортировка простым выбором
void List::sort_by_date() {
    if (first == last) return;

    Element *element_first = first;
    Element *element_second = first->next;
    Element *element_min;

    while (element_second) {
        element_min = element_first;
        while (element_second) {
            if (element_min->date->this_later_second(element_second->date))
                element_min = element_second;
            element_second = element_second->next;
        }
        if (element_min != element_first)
            swap(element_first, element_min);
        element_first = element_first->next;
        element_second = element_first->next;
    }
}

// удалить элемент по номеру
void List::remove_element_by_num(int num) {

    if (is_empty()) return;

    Element *element = first;

    if (num == 0) {
        // в списке один элемент
        if (first == last) {
            // удаление первого
            delete first;
            // направление указателей в никуда
            first = last = nullptr;
            return;
        }
        // удаление первого
        first = element->next;
        delete first->previous;
        first->previous = nullptr;
        // выход
        return;
    }

    // пройти нужное кол-во элементов
    for (int i = 0; i < num; i++) {
        if (element == nullptr) return;
        element = element->next;
    }

    // удаление элемента
    if (last == element) {
        element->previous->next = nullptr;
        last = element->previous;
        delete element;
    } else {
        element->previous->next = element->next;
        element->next->previous = element->previous;
        delete element;
    }
}

// создание нового списка с возвращенными элементами
List* List::create_new_with_back() {
    // создание списка
    List *list = new List();

    Element *element = first;

    // добавление элементов
    while (element) {
        if (element->back) {
            list->push_back(
                    element->id,
                    new Date(element->date),
                    element->value,
                    true
            );
        }
        element = element->next;
    }
    return list;
}

void List::push_back_random(int i) {
    string id;
    srand(time(NULL) + i);
    int count = 1 + rand() % 92;
    srand(time(NULL) + i);
    for (int i = 0; i < count; i++) {
        id += 'a' + rand() % 26;
    }
    srand(time(NULL) + i);
    push_back(
            id,
            new Date(1 + rand() * rand() % 30, 1 +rand() * 1000 % 11, rand() % 2023),
            rand(),
            rand() % 2 == 0
            );
}
