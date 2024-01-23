#include <iostream>
#include <ctime>
#include <cmath>


using namespace std;

// вывод матрицы на экран
void printMatrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

// заполнение матрицы случайными числами
void fillMatrixWithRandom(int **matrix, int n, int maxRandom) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % maxRandom * pow((-1), rand());
        }
    }
}

// алгоритм
int minChet(int **matrix, int n) {
    int k = 1; // отдаление от края строки
    int c = 0; // подсчёт сравнений
    int min = 2147483647; // минимальное значение
    for (int i = 0; i < n / 2 + n % 2 - 1; i++) {
        for (int j = k; j < n - k; j++) {
            c += 2; // за два if
            if (matrix[i][j] % 2 == 0 & matrix[i][j] < min) {
                min = matrix[i][j];
            }
            if (matrix[n - i - 1][j] % 2 == 0 & matrix[n - i - 1][j] < min) {
                min = matrix[n - i - 1][j];
            }
        }
        k++;
    }
    // был ли хоть один чётный элемент?
    if (min == 2147483647) {
        cout << "no such elements" << endl; // вывод сообщения об отсутствии подходящих элементов
        exit(-1); // завершение программы
    }
    cout << c << " comparisons" << endl;
    return min;
}

int main() {
    int n = 10;
    int **matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }
    fillMatrixWithRandom(matrix, n, 5);
    printMatrix(matrix, n);
    cout << minChet(matrix, n) << endl;
    return 0;
}
