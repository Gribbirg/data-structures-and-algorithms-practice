#include <iostream>

using namespace std;

struct Element {

    // значение элемента
    int value;

    // указатель на следующий элемент
    Element *nextElement;

    // конструктор
    Element(int value) : value(value), nextElement(nullptr) {}
};

struct List {
    Element *elementFirst;
    Element *elementLast;

    // конструктор
    List() : elementFirst(nullptr), elementLast(nullptr) {}

    // деструктор
    ~List() {

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
    bool is_empty() {
        return elementFirst == nullptr;
    }

    // добавление элемента в конец списка
    void push_back(int value) {

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

    // добавление элемента в начало списка
    void push_front(int value) {

        // создание нового элемента
        Element *elementNew = new Element(value);

        // если нет элементов
        if (is_empty()) {
            // новый элемент - последний
            elementLast = elementNew;
        }
        // следующий элемент - первый
        elementNew->nextElement = elementFirst;
        // новый элемент - первый
        elementFirst = elementNew;
    }

    // вывод списка
    void print() {

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

    // удалить элемент по значению
    void remove_element(int value) {

        // если ничего нет, то и делать ничего не надо
        if (is_empty())
            return;

        // указатели на текущий и следующий элементы
        Element *elementPrevious = elementFirst;
        Element *element = elementFirst->nextElement;

        // нужно удалить первый элемент
        if (elementFirst->value == value) {
            // в списке один элемент
            if (elementFirst == elementLast) {
                // удаление первого
                delete elementFirst;
                // направление указателей в никуда
                elementFirst = elementLast = nullptr;
                return;
            }
            // удаление первого
            delete elementFirst;
            // направление указателя в никуда
            elementFirst = element;
            // выход
            return;
        }

        // пока есть элементы
        while (element) {
            // нужно удалить текущий элемент
            if (element->value == value) {
                // удаление элемента
                if (element == elementLast) {
                    elementLast = elementPrevious;
                }
                elementPrevious->nextElement = element->nextElement;
                delete element;
                // выход
                return;
            }
            // следующий элемент
            elementPrevious = element;
            element = element->nextElement;
        }
        // такого элемента не оказалось
        cout << value << " does not exist!" << endl;
    }

    // найти элемент в следующий элементах
    bool find_element_in_next(Element *elementStart, int value) {

        // текущий элемент не существует
        if (!elementStart)
            return false;

        // текущий элемент искомый
        if (elementStart->value == value)
            return true;

        // рекурсивный вызов функции для следующего элемента
        return find_element_in_next(elementStart->nextElement, value);
    }

    // есть ли одинаковые элементы
    bool are_same_elements() {

        // перебор элементов
        Element *element = elementFirst;
        while (element) {
            // проверка, есть ли ещё такие же
            if (find_element_in_next(element->nextElement, element->value))
                return true;
            element = element->nextElement;
        }
        // нет одинаковых
        return false;
    }

    // удалить максимальный элемент
    void del_max() {

        if (is_empty())
            return;
        Element *element = elementFirst;
        int maxValue = element->value;
        element = element->nextElement;
        while (element) {
            if (element->value > maxValue) {
                maxValue = element->value;
            }
            element = element->nextElement;
        }
        remove_element(maxValue);
    }

    // добавить элемент перед элементами на чётных позициях
    void add_elements_before_evens(int value) {

        // если ничего нет, то и делать ничего не надо
        if (is_empty())
            return;

        // добавление элемента перед первым (нулевым)
        push_front(value);

        // первый элемент
        Element *elementPrevious = elementFirst->nextElement->nextElement;
        // если его нет, то закругляемся
        if (!elementPrevious)
            return;

        // второй элемент
        Element *elementNext = elementPrevious->nextElement;

        // пока есть элементы
        while (elementNext) {
            // создание элемента
            Element *element = new Element(value);

            // добавление элемента
            elementPrevious->nextElement = element;
            element->nextElement = elementNext;

            // следующие элементы
            elementPrevious = elementNext->nextElement;
            if (!elementPrevious)
                break;
            elementNext = elementPrevious->nextElement;
        }
    }
};

int main() {

    // дополнительные переменные
    int action;
    int n;
    int value;
    List* list = new List;

    // вывод информации о командах
    cout << "Select operation:\n"
            "0 - info\n"
            "1 - create list by values\n"
            "2 - print list\n"
            "3 - add element to the beginning\n"
            "4 - add element to the end\n"
            "5 - add element before elements at even positions\n"
            "6 - remove element by value\n"
            "7 - check if there are equal values\n"
            "8 - delete element with max value\n"
            "9 - clean list\n"
            "10 - exit\n";

    // основной цикл для ввода
    while (true) {

        // ввод номера команды
        cout << endl << "Enter command number:" << endl;
        cin >> action;
        switch (action) {
            case 0: // вывод информации о командах
                cout << "Select operation:\n"
                        "0 - info\n"
                        "1 - fill list with multiple values\n"
                        "2 - print list\n"
                        "3 - add element to the beginning\n"
                        "4 - add element to the end\n"
                        "5 - add element before elements at even positions\n"
                        "6 - remove element by value\n"
                        "7 - check if there are equal values\n"
                        "8 - delete element with max value\n"
                        "9 - clean list\n"
                        "10 - exit\n";
                break;
            case 1: // ввод сразу нескольких значений
                cout << "Enter count of elements:" << endl;
                cin >> n;
                for (int i = 0; i < n; i++) {
                    cout << "Enter value: ";
                    cin >> value;
                    list->push_back(value);
                    cout << endl;
                }
                break;
            case 2: // вывод списка
                cout << "List: ";
                list->print();
                break;
            case 3: // добавление элемента в начало
                cout << "Enter value: ";
                cin >> value;
                list->push_front(value);
                break;
            case 4: // добавление элемента в конец
                cout << "Enter value: ";
                cin >> value;
                list->push_back(value);
                break;
            case 5: // добавление элемента перед элементами на чётных позициях
                cout << "Enter value: ";
                cin >> value;
                list->add_elements_before_evens(value);
                break;
            case 6: // удаление элемента по значению
                cout << "Enter value: ";
                cin >> value;
                list->remove_element(value);
                break;
            case 7: // есть ли одинаковые значения
                if (list->are_same_elements()) {
                    cout << "There are same elements in the list" << endl;
                } else {
                    cout << "There are no same elements in the list" << endl;
                }
                break;
            case 8: // удаление максимального элемента
                list->del_max();
                cout << "Max element deleted" << endl;
                break;
            case 9: // отчистка списка
                delete list;
                list = new List;
                break;
            case 10: // выход
                delete list;
                return 0;
            default:
                cout << "Error. Try again!" << endl;
        }
    }
}
