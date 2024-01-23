#include "Date.h"
#include "Element.h"
#include "List.h"

using namespace std;

int main() {
    // дополнительные переменные
    int action;

    int n;
    string id;
    string date_str;
    double value;
    string back_str;
    Element *element;

    List *list = new List();
    List* newList;

//    list->push_back("220", new Date("23.10.1999"), 225.90, false);
//    list->push_back("221", new Date("23.5.2004"), 225.90, true);
//    list->push_back("222", new Date("23.10.2004"), 225.90, false);
//    list->push_back("223", new Date("23.10.2000"), 225.90, true);
//    list->push_back("224", new Date("23.08.2004"), 225.90, true);
//    list->sort_by_date();

    // вывод информации о командах
    cout << "Select operation:\n"
            "0 - info\n"
            "1 - create list by values\n"
            "2 - print list from left to right\n"
            "3 - print list from right to left\n"
            "4 - add element to the begin\n"
            "5 - add element to the end\n"
            "6 - remove elements by id and date\n"
            "7 - remove element by number\n"
            "8 - sort by date\n"
            "9 - find element by id\n"
            "10 - create new list\n"
            "11 - create new list with backed\n"
            "99 - exit\n";

    // основной цикл для ввода
    while (true) {


        // ввод номера команды
        cout << endl << "Enter command number:" << endl;
        cin >> action;

        // выполнение команды
        switch (action) {
            case 0:
                cout << "Select operation:\n"
                        "0 - info\n"
                        "1 - create list by values\n"
                        "2 - print list from left to right\n"
                        "3 - print list from right to left\n"
                        "4 - add element to the begin\n"
                        "5 - add element to the end\n"
                        "6 - remove elements by id and date\n"
                        "7 - remove element by number\n"
                        "8 - sort by date\n"
                        "9 - find element by id\n"
                        "10 - create new list\n"
                        "11 - create new list with backed\n"
                        "99 - exit\n";
                break;
            case 1:
                cout << "Enter count of elements:" << endl;
                cin >> n;
                for (int i = 0; i < n; i++) {
                    list->push_back_random(i);
                }
                break;
            case 2:
                cout << "List: " << endl;
                list->print_left_to_right();
                break;
            case 3:
                cout << "List: " << endl;
                list->print_right_to_left();
                break;
            case 4:
                cout << "New Element:" << endl;
                cout << "Enter id: ";
                cin >> id;
                cout << "Enter date(day.month.year): ";
                cin >> date_str;
                cout << "Enter value: ";
                cin >> value;
                cout << "Enter yes if it is backed else no: ";
                cin >> back_str;
                list->push_front(id, new Date(date_str), value, back_str == "yes");
                cout << "Complete" << endl;
                break;
            case 5:
                cout << "New Element:" << endl;
                cout << "Enter id: ";
                cin >> id;
                cout << "Enter date(day.month.year): ";
                cin >> date_str;
                cout << "Enter value: ";
                cin >> value;
                cout << "Enter yes if it is backed else no: ";
                cin >> back_str;
                list->push_back(id, new Date(date_str), value, back_str == "yes");
                cout << "Complete" << endl;
                break;
            case 6:
                cout << "Enter id: ";
                cin >> id;
                cout << "Enter date(day.month.year): ";
                cin >> date_str;
                list->remove_element(id, new Date(date_str));
                cout << "Complete" << endl;
                break;
            case 7:
                cout << "Enter number of element(started from 0): ";
                cin >> n;
                list->remove_element_by_num(n);
                cout << "Complete" << endl;
                break;
            case 8:
                list->sort_by_date();
                cout << "Complete" << endl;
                break;
            case 9:
                cout << "Enter id: ";
                cin >> id;
                element = list->find_element(id);
                if (element)
                    cout << "Id: " << element->id << " "
                         << "Date: " << element->date->in_string() << " "
                         << "Value: " << element->value << " "
                         << "Back: " << list->bool_to_string(element->back) << endl;
                break;
            case 10:
                delete list;
                list = new List();
                break;
            case 11:
                newList = list->create_new_with_back();
                delete list;
                list = newList;
                cout << "Complete" << endl;
                break;
            case 99: // выход
                delete list;
                return 0;
            default:
                cout << "Error. Try again!" << endl;
        }
        cout << endl;
    }
}
