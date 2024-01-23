#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

// вывод массива на экран, p - указатель на массив, n - кол-во элементов
void printMass(int *p, int n) {
    for (int i = 0; i < n; i++) {
        cout << p[i] << "\t";
    }
    cout << endl;
}

// заполнение массива случайными числами,
// p - указатель на массив, n - кол-во элементов,
// maxRandom - максимальное значение случайных чисел
void fillMassWithRandom(int *p, int n, int maxRandom) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        p[i] = rand() % maxRandom * pow(-1, rand());
    }
}

void fillMasssWithRandom(int *p1, int *p2, int n, int maxRandom) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        p1[i] = p2[i] = rand() % maxRandom * pow(-1, rand());
    }
}

// сортировка простыми вставками
void insertionSort(int *mass, int n) {
    int j, key;
    long long int k = 1; // за последнее сравнение в for

    // проходит по элементам массива, начиная со втрого
    for (int i = 1; i < n; i++) {
        k += 3;
        j = i - 1;
        key = mass[i];

        // пока jый эелемент больше "ключа" или массив не закончится
        while (j >= 0 && mass[j] > key) {
            // сдвиг элемента вправо
            k += 2;
            mass[j + 1] = mass[j];
            j--;
        }
        // вставка "ключа" на свободное место
        mass[j + 1] = key;
    }
    cout << k << " comparisons and movements insertionSort" << endl;
}

// сортировка простым выбором
void selectionSort(int *mass, int n) {
    int min, swap;
    long long int k = 1; // за последнее сравнение в for

    // перебираем элементы массива, кроме последнего
    for (int i = 0; i < n - 1; i++) {
        k += 3;
        min = i;
        // нахождение минимального элемента правее iого
        for (int j = i + 1; j < n; j++) {
            k += 2;
            if (mass[j] < mass[min])
                min = j;
        }
        if (min != i) {
            k += 3;
            swap = mass[i];
            mass[i] = mass[min];
            mass[min] = swap;
        }
    }
    cout << k << " comparisons and movements selectionSort" << endl;
}

int main()
{
    // размерность массива
    int n = 10;

    // выделение памяти под массив
    int *mass1 = new int[n];
    int *mass2 = new int[n];

    // заполнение массива случайными цифрами
    fillMasssWithRandom(mass1, mass2, n, 1000);

    // заполнение массива по убыванию/возрастанию
    //for (int i = 0; i < n; i ++) {
    //    mass[n - i - 1] = i;
    //}

    // вывод массива до
   cout << "Before:" << endl;
    printMass(mass1, n);


    time_t begin = clock();

    insertionSort(mass1, n);

    // подсчёт времени выполнения алгоритма
    time_t end = clock();
    double time_spent = (double) (end - begin);
    cout << "Time insertionSort: " << time_spent << endl;

    begin = clock();

    selectionSort(mass2, n);

    // подсчёт времени выполнения алгоритма
    end = clock();
    time_spent = (double) (end - begin);
    cout << "Time selectionSort: " << time_spent << endl;

    // вывод массива после
    cout << "After:" << endl;
    printMass(mass1, n);
    cout << "After:" << endl;
    printMass(mass2, n);

    return 0;
}
