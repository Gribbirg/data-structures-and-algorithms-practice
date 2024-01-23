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

//заполнить три массива одинаковыми случайными значениями
void fillMasssWithRandom(int *p1, int *p2, int *p3, int n, int maxRandom) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        p1[i] = p2[i] = p3[i] = rand() % maxRandom * pow(-1, rand());
    }
}


// поменять элементы местами
void swapEl(int *a, int *b) {
    int v = *a;
    *a = *b;
    *b = v;
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

// функция для построения кучи
void heapify(int *mass, int n, int i, long long int *k) {

    // старший элемент тройки
    int largest = i;

    // дочерние элементы
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    (*k) += 3;
    // нахождение наибольшего элемента
    if (left < n && mass[left] > mass[largest])
        largest = left;
    if (right < n && mass[right] > mass[largest])
        largest = right;

    // если наибольшим оказался не первоначально старший элемент
    if (largest != i) {

        (*k) += 3;
        // замена старшего и наибольшего элемента
        swapEl(&mass[i], &mass[largest]);

        // рекурсивный вызов функции к номеру наибольшего элемента
        heapify(mass, n, largest, k);
    }
}

// пирамидальная сортировка
void heapSort(int *mass, int n, long long int *k) {

    (*k)++;
    // построение кучи
    for (int i = n / 2; i >= 0; i--) {
        (*k)++;
        heapify(mass, n, i, k);
    }

    (*k)++;
    // сортировка массива
    for (int i = n - 1; i >= 0; i--) {
        (*k) += 4;
        // замена первого и последнего неотсортированного элемента
        swapEl(&mass[0], &mass[i]);

        // построение новой кучи
        heapify(mass, i, 0, k);
    }
}


// слияние массивов
void merge(int *mass, int left, int mid, int right, long long int *k) {
    // размерности двух массивов
    int sub1 = mid - left + 1;
    int sub2 = right - mid;

    // создание двух массивов
    int *leftMass = new int[sub1];
    int *rightMass = new int[sub2];

    (*k)++;
    // заполнение этих массивов
    for (int i = 0; i < sub1; i++) {
        (*k) += 2;
        leftMass[i] = mass[left + i];
    }
    (*k)++;
    for (int j = 0; j < sub2; j++) {
        (*k) += 2;
        rightMass[j] = mass[mid + 1 + j];
    }

    // счетчики кол-ва переписанных элементов массивов
    int iSub1 = 0;
    int iSub2 = 0;

    // счётчик кол-ва элементов в результирующем массиве
    int iMerMass = left;

    (*k)++;
    // пока в обоих массивах есть элементы
    while (iSub1 < sub1 && iSub2 < sub2) {

        (*k) += 2;
        // элемент левого массива меньше или равен
        if (leftMass[iSub1] <= rightMass[iSub2]) {

            // элемент левого массива записываем в результирующий
            mass[iMerMass] = leftMass[iSub1];
            iSub1++;

        }

            // элемент правого массива меньше
        else {

            // элемент правого массива записываем в результирующий
            mass[iMerMass] = rightMass[iSub2];
            iSub2++;

        }

        // увеличиваем кол-во элементов в результирующем массиве
        iMerMass++;
    }

    (*k)++;
    // переписываем оставшиеся элементы из левого массива
    while (iSub1 < sub1) {
        (*k) += 2;
        mass[iMerMass] = leftMass[iSub1];
        iSub1++;
        iMerMass++;
    }

    (*k)++;
    // переписываем оставшиеся элементы из правого массива
    while (iSub2 < sub2) {
        (*k) += 2;
        mass[iMerMass] = rightMass[iSub2];
        iSub2++;
        iMerMass++;
    }
    // удаляем левый и правый массивы
    delete[] leftMass;
    delete[] rightMass;
}

// сортировка слиянием
void mergeSort(int *mass, int begin, int end, long long int *k) {

    (*k)++;
    // если номер начального элемента больше номера конечного, то выходим
    if (begin >= end)
        return;

    // разделение массива пополам
    int mid = begin + (end - begin) / 2;

    // рекурсивный вызов функции для левой и правой частей
    mergeSort(mass, begin, mid, k);
    mergeSort(mass, mid + 1, end, k);

    // слияние левой и правой части
    merge(mass, begin, mid, end, k);

}

int main() {
    // размерность массива
    int n = 10;
    cout << "n = " << n << endl;

    // выделение памяти под массив
    int *mass1 = new int[n];
    int *mass2 = new int[n];
    int *mass3 = new int[n];

    long long int *k = new long long int;

    // заполнение массива случайными цифрами
    fillMasssWithRandom(mass1, mass2, mass3, n, 1000);

    // заполнение массива по убыванию/возрастанию
//    for (int i = 0; i < n; i ++) {
//        mass2[n - i - 1] = i;
//        mass3[n - i - 1] = i;
//    }

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
    *k = 0;
    heapSort(mass2, n, k);
    cout << *k << " comparisons and movements heapSort" << endl;

    // подсчёт времени выполнения алгоритма
    end = clock();
    time_spent = (double) (end - begin);
    cout << "Time heapSort: " << time_spent << endl;


    begin = clock();
    *k = 0;
    mergeSort(mass3, 0, n - 1, k);
    cout << *k << " comparisons and movements mergeSort" << endl;

    // подсчёт времени выполнения алгоритма
    end = clock();
    time_spent = (double) (end - begin);
    cout << "Time mergeSort: " << time_spent << endl;



    // вывод массива после
    cout << "After insertionSort:" << endl;
    printMass(mass1, n);

    cout << "After heapSort:" << endl;
    printMass(mass2, n);

    cout << "After mergeSort:" << endl;
    printMass(mass3, n);

    delete []mass1;
    delete []mass2;
    delete []mass3;

    return 0;
}
