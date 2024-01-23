//
// Created by gribk on 02.10.2023.
//

#include <iomanip>
#include "HashTable.h"

#include "../PhoneOwnerExtended.h"

void HashTable::HashTableRow::print() {
    string phoneStr, positionStr, freeStr, deletedStr;
    if (phone.empty()) {
        phoneStr = "none";
        positionStr = "none";
    } else {
        phoneStr = phone;
        positionStr = to_string(position);
    }
    if (free) freeStr = "True";
    else freeStr = "False";
    if (deleted) deletedStr = "True";
    else deletedStr = "False";

    cout << "phone: " << setw(20) << phoneStr
         << ", position: " << setw(10) << positionStr
         << ", is free: " << setw(8) << freeStr
         << ", was deleted: " << setw(8) << deletedStr;
}

HashTable::HashTableRow::HashTableRow(string phone, int position) : phone(std::move(phone)),
                                                                    position(position) {
    free = false;
    deleted = false;
}

HashTable::HashTableRow::HashTableRow() {
    phone = "";
    position = 0;
    free = true;
    deleted = false;
}

HashTable::HashTable(unsigned int size) {
    this->size = size;
    busy = 0;
    table = new HashTableRow[size];
}

unsigned int HashTable::hesh(unsigned long long int phone, unsigned int size) {
    return phone % size;
}

unsigned int HashTable::biasHesh(unsigned long long int phone, unsigned int size) {
    unsigned int bias = (phone / size) % size;
    return bias == 0 || size % bias == 0 ? 1 : bias;
}

bool HashTable::insert(const string &phone, int position, bool outIndexes) {

    if (findElement(phone) != -1)
        return false;

    unsigned int num = hesh(PhoneOwnerExtended::phoneToLong(phone), size);
    unsigned bias = biasHesh(PhoneOwnerExtended::phoneToLong(phone), size);

    if (outIndexes) {
        cout << "Hash: " << num << endl;
        cout << "Bias: " << bias % size << endl;
        cout << "Indexes:";
    }

    while (!table[num].free) {
        num = (num + bias) % size;
        if (outIndexes)
            cout << ' ' << num;
    }

    if (outIndexes)
        cout << endl;

    table[num] = HashTableRow(phone, position);

    busy++;
    if (size * 0.75 < busy)
        update(getOptimizedSize(size));

    return true;
}

unsigned int HashTable::getOptimizedSize(unsigned int busy) {
    if (busy <= 1) return 5;
    busy = busy * 2;
    while (!isEasy(busy))
        busy++;
    return busy;
}


void HashTable::update(unsigned int sizeNew) {
    HashTableRow *tableOld = table;
    unsigned int sizeOld = size;
    size = sizeNew;
    busy = 0;
    table = new HashTableRow[size];
    for (int i = 0; i < sizeOld; i++) {
        if (!tableOld[i].free) {
            insert(tableOld[i].phone, tableOld[i].position);
        }
    }
    delete[] tableOld;
}

bool HashTable::isEasy(unsigned long long int x) {
    for (int i = 2; i <= x / 2; i++)
        if (x % i == 0)
            return false;
    return true;
}

void HashTable::printTable() {
    cout << "Hash table for " << size << " elements with " << busy << " inside:" << endl;
    for (int i = 0; i < size; i++) {
        cout << setw(8) << i << ": ";
        table[i].print();
        cout << '\n';
    }
}

void HashTable::exportToFile(fstream &resultFile) {
    resultFile.open("result.txt", ios::out | ios::trunc);
    if (!resultFile.is_open()) {
        cout << "Error while opening file!" << endl;
        exit(0);
    }
    resultFile.clear();
    string phoneStr, positionStr, freeStr, deletedStr;
    resultFile << setw(25) << "Number"
               << setw(25) << "Phone"
               << setw(25) << "Position"
               << setw(25) << "Is free"
               << setw(25) << "Was deleted" << '\n';
    for (int i = 0; i < size; i++) {
        if (table[i].phone.empty()) {
            phoneStr = "none";
            positionStr = "none";
        } else {
            phoneStr = table[i].phone;
            positionStr = to_string(table[i].position);
        }
        if (table[i].free) freeStr = "True";
        else freeStr = "False";
        if (table[i].deleted) deletedStr = "True";
        else deletedStr = "False";

        resultFile << setw(25) << i
                   << setw(25) << phoneStr
                   << setw(25) << positionStr
                   << setw(25) << freeStr
                   << setw(25) << deletedStr << '\n';
    }
    resultFile.close();
}

int HashTable::find(const string &phone) {

    int num = findElement(phone);
    if (num != -1)
        return table[num].position;

    return -1;
}

unsigned int HashTable::getSize() const {
    return size;
}

unsigned int HashTable::getBusy() const {
    return busy;
}

int HashTable::deleteElement(const string &phone) {
    int num = findElement(phone);

    if (num != -1) {
        table[num].deleted = true;
        table[num].free = true;
        busy--;
        int position = table[num].position;
        if (size * 0.1 > busy)
            update(getOptimizedSize(busy / 0.75));
        return position;
    }

    return -1;
}

void HashTable::reducePosition(const string &phone) {
    int num = findElement(phone);
    if (num != -1)
        table[num].position--;
}

int HashTable::findElement(const string &phone) {
    unsigned int num = hesh(PhoneOwnerExtended::phoneToLong(phone), size);
    unsigned int bias = biasHesh(PhoneOwnerExtended::phoneToLong(phone), size);

    while (!table[num].free || table[num].deleted) {
        if (!table[num].free && table[num].phone == phone) {
            return num;
        }
        num = (num + bias) % size;
    }
    return -1;
}

HashTable::~HashTable() {
    delete[] table;
}


