#include <iostream>
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
        p[i] = rand() % maxRandom;
    }
}

// первый алгоритм
int delFirstMetod(int *x, int n, int key) {
    int i = 0;
    int k = 1; // подсчёт количества сравнений, учёт первой итерации while
    while (i < n) {
        k += 2; // за while и if
        if (x[i] == key) {
            for (int j = i; j < n - 1; j++) {
                x[j] = x[j + 1];
                k += 2; // за for и перемещение
            }
            k++; // последнее сравнение в for
            n--;
        } else {
            i++;
        }
    }
    cout << k << " comparisons and movements" << endl;
    return n;
}

// второй алгоритм
int delOtherMetod(int *x, int n, int key) {
    int j = 0;
    int k = 1; // подсчёт количества сравнений, учёт первой итерации for
    for (int i = 0; i < n; i++) {
        x[j] = x[i];
        k += 3; // за for, перемещение и if
        if (x[i] != key) {
            j++;
        }
    }
    n = j;
    cout << k << " comparisons and movements" << endl;
    return n;
}

int main() {
    // длина массива
    int n = 10;
    // указатель на массив:
    int *p = new int[n]{2, 2, 2, 2, 2, 2, 2, 2, 2, 2};

    printMass(p, n);
    printMass(p, delFirstMetod(p, n, p[rand() % n]));
    return 0;
}
