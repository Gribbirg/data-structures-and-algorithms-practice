#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

// разделение файла по порциям
void divideFile(int n) {

    // открытие файлов
    ifstream outA;
    outA.open("C:\\Users\\gribk\\CLionProjects\\Alg\\4\\A.txt");

    ofstream inB;
    inB.open("C:\\Users\\gribk\\CLionProjects\\Alg\\4\\B.txt");

    ofstream inC;
    inC.open("C:\\Users\\gribk\\CLionProjects\\Alg\\4\\C.txt");

    int i;
    string line;

    if (outA.is_open() && inB.is_open() && inC.is_open()) {
        while (getline(outA, line)) {
            // запись n строк в В
            inB << line << endl;
            for (i = 0; i < n - 1 && getline(outA, line); i++) {
                inB << line << endl;
            }
            // запись n строк в С
            for (i = 0; i < n && getline(outA, line); i++) {
                inC << line << endl;
            }
        }
        // закрытие файлов
        outA.close();
        inB.close();
        inC.close();
    } else { // если файлы не открылись
        cout << "Files not opened!" << endl;
        exit(8);
    }
}

// прямое слияние
int merge(int n) {

    // открытие файлов
    ofstream inA;
    inA.open("C:\\Users\\gribk\\CLionProjects\\Alg\\4\\A.txt");

    ifstream outB;
    outB.open("C:\\Users\\gribk\\CLionProjects\\Alg\\4\\B.txt");
    int sizeB = 0;
    int sizeBFile = 0;

    ifstream outC;
    outC.open("C:\\Users\\gribk\\CLionProjects\\Alg\\4\\C.txt");
    int sizeC = 0;

    string lineB, lineC;
    int idB, idC;


    if (inA.is_open() && outB.is_open() && outC.is_open()) {

        // чтение номера и строки
        outB >> idB;
        outC >> idC;
        getline(outB, lineB);
        getline(outC, lineC);

        while (outB && outC) {
            // в обоих порциях ещё есть элементы
            if (sizeB < n && sizeC < n) {
                // элемент в В меньше
                if (idB <= idC) {
                    inA << idB << lineB << endl;
                    sizeB++;
                    sizeBFile++;
                    outB >> idB;
                    getline(outB, lineB);
                } else {
                    inA << idC << lineC << endl;
                    sizeC++;
                    outC >> idC;
                    getline(outC, lineC);
                }
            } else if (sizeB < n) { // только в В есть элементы
                inA << idB << lineB << endl;
                sizeB++;
                sizeBFile++;
                outB >> idB;
                getline(outB, lineB);
            } else if (sizeC < n) { // только в С есть элементы
                inA << idC << lineC << endl;
                sizeC++;
                outC >> idC;
                getline(outC, lineC);
            } else { // обе порции закончились
                sizeB = 0;
                sizeC = 0;
            }
        }
        // копирование оставшихся элементов из файлов
        while (outB) {
            inA << idB << lineB << endl;
            sizeBFile++;
            outB >> idB;
            getline(outB, lineB);
        }
        while (outC) {
            inA << idC << lineC << endl;
            outC >> idC;
            getline(outC, lineC);
        }
        inA.close();
        outB.close();
        outC.close();
    } else {
        cout << "Files not opened!" << endl;
        exit(8);
    }
    return sizeBFile; // размер порции
}

// сортировка прямым слиянием
void directMergeSort() {
    // деление файла на порции
    divideFile(1);
    for (int i = 1; i < merge(i); i *= 2) { // слияние
        divideFile(i * 2); // деление файла на порции
    }
}

// сортировка простым выбором
void selectionSort(int *massId, string *massStr, int n) {
    int min, swapId;
    string swapStr;

    // перебираем элементы массива, кроме последнего
    for (int i = 0; i < n - 1; i++) {
        min = i;
        // нахождение минимального элемента правее iого
        for (int j = i + 1; j < n; j++) {
            if (massId[j] < massId[min])
                min = j;
        }
        if (min != i) {
            swapId = massId[i];
            massId[i] = massId[min];
            massId[min] = swapId;

            swapStr = massStr[i];
            massStr[i] = massStr[min];
            massStr[min] = swapStr;
        }
    }
}

// разделение файла на фиксированные серии с сортировкой
void seriesFixedDivideFiles(int sizeSeries) {
    // открытие файлов
    ifstream outA;
    outA.open("C:\\Users\\gribk\\CLionProjects\\Alg\\4\\A2.txt");

    ofstream inB;
    inB.open("C:\\Users\\gribk\\CLionProjects\\Alg\\4\\B.txt");

    ofstream inC;
    inC.open("C:\\Users\\gribk\\CLionProjects\\Alg\\4\\C.txt");

    int *massId = new int[sizeSeries];
    string *massStr = new string[sizeSeries];
    int iMass = 0;

    int i;
    string lineA;
    int idA;
    bool nextB = true;

    if (outA.is_open() && inB.is_open() && inC.is_open()) {

        // чтение номера и строки
        outA >> idA;
        getline(outA, lineA);

        // пока в А есть эелементы
        while (outA) {

            // запись в память
            massId[iMass] = idA;
            massStr[iMass] = lineA;
            iMass++;

            // массив заполнен
            if (iMass == sizeSeries) {

                // сортировка массива
                selectionSort(massId, massStr, iMass);

                // запись массива в нужный файл
                if (nextB) {
                    for (i = 0; i < iMass; i++) {
                        inB << massId[i] << massStr[i] << endl;
                    }
                    // смена следующего файла
                    nextB = false;
                } else {
                    for (i = 0; i < iMass; i++) {
                        inC << massId[i] << massStr[i] << endl;
                    }
                    // смена следующего файла
                    nextB = true;
                }
                iMass = 0;

            }

            // чтение номера и строки
            outA >> idA;
            getline(outA, lineA);

        }

        // запись оставшегося массива
        if (iMass > 0) {
            selectionSort(massId, massStr, iMass);

            if (nextB) {
                for (i = 0; i < iMass; i++) {
                    inB << massId[i] << massStr[i] << endl;
                }
                nextB = false;
            } else {
                for (i = 0; i < iMass; i++) {
                    inC << massId[i] << massStr[i] << endl;
                }
                nextB = true;
            }

        }

        outA.close();
        inB.close();
        inC.close();
    } else {
        cout << "Files not opened!" << endl;
        exit(8);
    }

    delete[] massId;
    delete[] massStr;

}

// разделение файла на серии
void seriesDivideFiles() {
    // открытие файлов
    ifstream outA;
    outA.open("C:\\Users\\gribk\\CLionProjects\\Alg\\4\\A2.txt");

    ofstream inB;
    inB.open("C:\\Users\\gribk\\CLionProjects\\Alg\\4\\B.txt");

    ofstream inC;
    inC.open("C:\\Users\\gribk\\CLionProjects\\Alg\\4\\C.txt");

    string lineA, lineANext;
    int idA, idANext;
    bool fileB = true;

    if (outA.is_open() && inB.is_open() && inC.is_open()) {

        // чтение текущей и следующей строк
        outA >> idA;
        getline(outA, lineA);
        outA >> idANext;
        getline(outA, lineANext);

        while (outA) {
            // запись в текущий файл
            if (fileB)
                inB << idA << lineA << endl;
            else
                inC << idA << lineA << endl;

            // серия закончилась
            if (idA > idANext) {
                // смена файла
                fileB = !(fileB);
            }

            idA = idANext;
            lineA = lineANext;

            outA >> idANext;
            getline(outA, lineANext);
        }

        // запись последней строки
        if (fileB)
            inB << idA << lineA << endl;
        else
            inC << idA << lineA << endl;

        outA.close();
        inB.close();
        inC.close();
    } else {
        cout << "Files not opened!" << endl;
        exit(8);
    }
}

// натуральное слияние
bool naturalMerge() {

    ofstream inA;
    inA.open("C:\\Users\\gribk\\CLionProjects\\Alg\\4\\A2.txt");

    ifstream outB;
    outB.open("C:\\Users\\gribk\\CLionProjects\\Alg\\4\\B.txt");
    bool lastB = false;
    bool lastInFileB = false;

    ifstream outC;
    outC.open("C:\\Users\\gribk\\CLionProjects\\Alg\\4\\C.txt");
    bool lastC = false;
    bool lastInFileC = false;

    string lineB, lineC, lineBNext, lineCNext;
    int idB, idC, idBNext, idCNext;


    if (inA.is_open() && outB.is_open() && outC.is_open()) {

        // чтение текущих и следующих строк
        outB >> idB;
        getline(outB, lineB);
        outB >> idBNext;
        getline(outB, lineBNext);
        outC >> idC;
        getline(outC, lineC);
        outC >> idCNext;
        getline(outC, lineCNext);

        // размер серии равен всем записям
        if (!outB) {
            inA << idC << lineC << endl;
            inA << idCNext << lineCNext << endl;
            while (getline(outC, lineC)) {
                inA << lineC << endl;
            }
            inA.close();
            outB.close();
            outC.close();
            return true;
        }
        if (!outC) {
            inA << idB << lineB << endl;
            inA << idBNext << lineBNext << endl;
            while (getline(outB, lineB)) {
                inA << lineB << endl;
            }
            inA.close();
            outB.close();
            outC.close();
            return true;
        }

        while (true) {
            if (!lastC && !lastB) { // серии не хакончились
                if (idB <= idC) {
                    if (idB > idBNext) {
                        lastB = true;
                    }
                    inA << idB << lineB << endl;
                    idB = idBNext;
                    lineB = lineBNext;
                    outB >> idBNext;
                    getline(outB, lineBNext);
                    if (lastInFileB) { // последний в файле
                        inA << idC << lineC << endl;
                        if (!lastInFileC)
                            inA << idCNext << lineCNext << endl;
                        break;
                    }
                } else {
                    if (idC > idCNext) {
                        lastC = true;
                    }
                    inA << idC << lineC << endl;
                    idC = idCNext;
                    lineC = lineCNext;
                    outC >> idCNext;
                    getline(outC, lineCNext);
                    if (lastInFileC) {
                        inA << idB << lineB << endl;
                        if (!lastInFileB)
                            inA << idBNext << lineBNext << endl;
                        break;
                    }
                }
            } else if (!lastC) { // только в серии в С остались
                if (idC > idCNext) {
                    lastC = true;
                }
                inA << idC << lineC << endl;
                idC = idCNext;
                lineC = lineCNext;
                outC >> idCNext;
                getline(outC, lineCNext);
                if (lastInFileC) {
                    inA << idB << lineB << endl;
                    if (!lastInFileB)
                        inA << idBNext << lineBNext << endl;
                    break;
                }
            } else if (!lastB) { // только в серии в В остались
                if (idB > idBNext) {
                    lastB = true;
                }
                inA << idB << lineB << endl;
                idB = idBNext;
                lineB = lineBNext;
                outB >> idBNext;
                getline(outB, lineBNext);
                if (lastInFileB) {
                    inA << idC << lineC << endl;
                    if (!lastInFileC)
                        inA << idCNext << lineCNext << endl;
                    break;
                }
            } else { // серии закончились
                lastB = false;
                lastC = false;
            }

            // в файле остался последний элемент
            if (!outB)
                lastInFileB = true;
            if (!outC)
                lastInFileC = true;
        }

        // докопирование файлов
        while (getline(outB, lineB))
            inA << lineB << endl;
        while (getline(outC, lineC))
            inA << lineC << endl;

        inA.close();
        outB.close();
        outC.close();
    } else {
        cout << "Files not opened!" << endl;
        exit(8);
    }
    return false; // не последнее слияние
}

// сортировка натуральным слиянием
void naturalMergeSort(int n) {

    // разделение файла с фиксированной серией
    seriesFixedDivideFiles(n);

    // копирование в один файл
    ofstream inA;
    inA.open("C:\\Users\\gribk\\CLionProjects\\Alg\\4\\A2.txt");

    ifstream outB;
    outB.open("C:\\Users\\gribk\\CLionProjects\\Alg\\4\\B.txt");

    ifstream outC;
    outC.open("C:\\Users\\gribk\\CLionProjects\\Alg\\4\\C.txt");

    string line;

    if (inA.is_open() && outB.is_open() && outC.is_open()) {
        while (getline(outB, line)) {
            inA << line << endl;
        }
        while (getline(outC, line)) {
            inA << line << endl;
        }

        inA.close();
        outB.close();
        outC.close();
    } else {
        cout << "Files not opened!" << endl;
        exit(8);
    }

    do {
        seriesDivideFiles(); // разделение
    } while (!naturalMerge()); // слияние
}

int main() {

    time_t begin = clock();

    directMergeSort();

    // подсчёт времени
    time_t end = clock();
    double time_spent = (double) (end - begin);
    cout << "Direct merge sort time: " << time_spent << endl;

    begin = clock();

    naturalMergeSort(4);

    // подсчёт времени
    end = clock();
    time_spent = (double) (end - begin);
    cout << "Natural merge sort time: " << time_spent << endl;

    return 0;
}
