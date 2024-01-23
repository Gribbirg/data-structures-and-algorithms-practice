#include <iostream>
#include <cmath>
#include <ctime>
#include "List.h"

using namespace std;

// заполнение массива случайными числами,
// p - указатель на массив, n - кол-во элементов,
// maxRandom - максимальное значение случайных чисел
void fillMassWithRandom(int *p, int n, int maxRandom) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        p[i] = rand() % maxRandom * pow(-1, rand());
    }
}

// рекурсивный алгоритм создания очереди
List *rec_create_list(bool random = false, List *list = new List()) {

    // переменная для ввода
    string enter;
    int value;
    if (random) {
        if (!list->is_empty()) {
            cout << " Continue? 'No' if stop\n";
            cin >> enter;
        }
        if (enter == "No") return list;

        srand(time(NULL));
        value = rand() % 1000 * pow(-1, rand());
        cout << value << endl;
    } else {
        cin >> enter;
        // проверка на конец
        if (enter == "END") return list;
        value = stoi(enter);
    }

    // добавление элемента
    list->push_back(value);

    // переход к добавлению следующего элемента
    return rec_create_list(random, list);
}

// итерационный алгоритм нахождения максимального элемента в массиве
int iter_max_in_mass(int *mass, int len, int *k) {

    // переменная для максимального текущего
    int max = mass[0];

    (*k) ++;
    // перебор элементов
    for (int i = 1; i < len; i++) {
        (*k) += 2;
        // обновление максимального
        if (mass[i] > max) {
            max = mass[i];
        }
    }

    // возврат максимального
    return max;
}

// рекурсивный алгоритм нахождения максимального элемента в массиве
int rec_max_in_mass(int *mass, int len, int *k) {

    (*k)++;
    // если массив из одного элемента, то возвращаем его
    if (len == 1) return mass[0];

    (*k)++;
    // возврат максимального из текущего и максимального из элементов до него
    return max(mass[len - 1], rec_max_in_mass(mass, len - 1, k));
}

int main() {

    // дополнительные переменные
    int len;
    int *mass = nullptr;
    List *list_rec = nullptr;
    List *list_iter = nullptr;
    string rand;
    int *k = new int;

    // команды
    int command;
    cout << "Select operation:\n"
            "0 - info\n"
            "1 - find max in mass\n"
            "2 - create queue on list\n"
            "9 - exit\n\n";

    while (true) {
        cin >> command;
        switch (command) {

            case 0: // информация

                cout << "Select operation:\n"
                        "0 - info\n"
                        "1 - find max in mass\n"
                        "2 - create queue on list\n"
                        "9 - exit\n";
                break;

            case 1: // нахождение максимального

                cout << "Enter len of mass:\n";
                cin >> len;

                mass = new int[len];

                cout << "Rand? Yes/No\n";
                cin >> rand;

                if (rand == "Yes")
                    fillMassWithRandom(mass, len, 100);
                else {
                    for (int i = 0; i < len; i++) {
                        cout << "Enter element number " << i << ":\n";
                        cin >> mass[i];
                    }
                }
                cout << "\nMass:";
                for (int i = 0; i < len; i++) {
                    cout << " " << mass[i];
                }
                cout << endl;

                (*k) = 0;
                cout << "Iterative result: " << iter_max_in_mass(mass, len, k) << endl;
                cout << (*k) << " operations" << endl;

                (*k) = 0;
                cout << "Recursive result: " << rec_max_in_mass(mass, len, k) << endl;
                cout << (*k) << " operations" << endl;

                break;

            case 2: // создание очереди

                cout << "Rand? Yes/No\n";
                cin >> rand;

                if (rand == "Yes")
                    list_rec = rec_create_list(true);
                else {
                    cout << "Enter END to end\n\n";
                    list_rec = rec_create_list();
                }

                cout << "Recursive result: ";
                list_rec->print();

                break;

            case 9: // завершение работы

                // удаление динамических переменных
                delete mass;
                delete list_iter;
                delete list_rec;

                return 0;

            default: // ошибка ввода

                cout << "Error. Try again!" << endl;
                break;
        }
        cout << endl;
    }
}
