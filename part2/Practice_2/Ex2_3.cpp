//
// Created by gribk on 22.09.2023.
//

#include "Ex2_3.h"
#include "PhoneOwner.h"
#include <iostream>
#include <utility>
#include <algorithm>
#include <cmath>
#include <ctime>

Ex2_3::BinOffsetTablePow::BinOffsetTablePow(string phone, unsigned int position) : phone(std::move(phone)),
                                                                                   position(position) {}

string Ex2_3::BinOffsetTablePow::to_string() {
    return "Phone: " + phone + ", position: " + std::to_string(position);
}

bool Ex2_3::BinOffsetTablePow::operator<(const Ex2_3::BinOffsetTablePow &rhs) const {
    return phone < rhs.phone;
}

void Ex2_3::start(fstream &fstream1) {

    time_t startTime = clock();

    vector<BinOffsetTablePow> table = generateBinOffsetTable(fstream1);
    sort(table.begin(), table.end());

    if (table.size() % 2 == 0) table.insert(table.begin(), BinOffsetTablePow("", 0));
    vector<int> delta = generateDelta(table.size());

    time_t endTime = clock();
    cout << "Preparation time: " << (double) (endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;


    unsigned int enter;
    cout << "Print bin offset table? (1 - yes, 0 - no): ";
    cin >> enter;
    if (enter == 1) {
        cout << endl;
        printBinOffsetTable(table);
        cout << endl;
    }

    string phoneNumber;

    do {

        cout << "Enter the phone number you are looking for (format: +7 (XXX) XXX-XX-XX): ";
        while (getline(cin, phoneNumber) && phoneNumber.empty());
        cout << endl;

        startTime = clock();
        int pos = binarySearch(table, delta, phoneNumber, delta[0], 1);
        if (pos == -1)
            cout << "Number " << phoneNumber << " is not founded" << endl;
        else
            cout << getPhoneOwnerFromBin(fstream1, pos).to_string() << endl;
        endTime = clock();

        cout << "Search time: " << (double) (endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
        cout << endl;

        cout << "Search next phone owner? (1 - yes, 0 - no): ";
        cin >> enter;

    } while (enter == 1);
}

// предусловие: наличие потока, удачное открытие файла
// постусловие: таблица доступа к записи в файле
vector<Ex2_3::BinOffsetTablePow> Ex2_3::generateBinOffsetTable(fstream &binFile) {

    binFile.open("bin.dat", ios::in | ios::binary);

    vector<BinOffsetTablePow> table;

    if (!binFile.is_open()) {
        cout << "Error while opening file!" << endl;
        exit(0);
    }

    unsigned int i = 0;
    PhoneOwner phoneOwner{};
    binFile.read((char *) &phoneOwner, sizeof(PhoneOwner));

    while (!binFile.eof()) {
        table.emplace_back(phoneOwner.phone, i);
        binFile.read((char *) &phoneOwner, sizeof(PhoneOwner));
        i++;
    }

    binFile.close();

    return table;
}

void Ex2_3::printBinOffsetTable(const vector<BinOffsetTablePow> &binOffsetTable) {
    for (BinOffsetTablePow binOffsetTablePow: binOffsetTable) cout << binOffsetTablePow.to_string() << endl;
}

// предусловие: длинна таблицы доступа
// постусловие: таблица смещений
vector<int> Ex2_3::generateDelta(unsigned int size) {
    vector<int> delta;
    size--;
    for (int i = 1; i <= log2(size) + 2; i++)
        delta.push_back((size + pow(2, i - 1)) / (pow(2, i)));
    return delta;
}

// предусловие: наличие таблиц, искомого номера телефона, а так же переменных
// постусловие: рекурсивный запуск алгоритма; в конце - позиция искомого номера телефона в бинарном файле
int
Ex2_3::binarySearch(const vector<BinOffsetTablePow> &binOffsetTable,
                    const vector<int> &delta,
                    const string &phone,
                    unsigned int i,
                    unsigned int j) {

    if (phone < binOffsetTable[i].phone) {
        if (delta[j] == 0) return -1;
        else return binarySearch(binOffsetTable, delta, phone, i - delta[j], j + 1);
    }
    if (phone > binOffsetTable[i].phone) {
        if (delta[j] == 0) return -1;
        else return binarySearch(binOffsetTable, delta, phone, i + delta[j], j + 1);
    }
    return binOffsetTable[i].position;
}

// предусловие: наличие потока, удачное открытие файла, позиция искомой записи
// постусловие: искомая запись
PhoneOwner Ex2_3::getPhoneOwnerFromBin(fstream &binFile, int position) {

    binFile.open("bin.dat", ios::in | ios::binary);

    PhoneOwner phoneOwner{};

    binFile.seekg(position * sizeof(PhoneOwner), ios::beg);
    binFile.read((char *) &phoneOwner, sizeof(PhoneOwner));

    binFile.close();

    return phoneOwner;
}


