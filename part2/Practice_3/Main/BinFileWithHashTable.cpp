//
// Created by gribk on 02.10.2023.
//

#include <algorithm>
#include <cstring>
#include <utility>
#include "BinFileWithHashTable.h"
#include "../PhoneOwnerExtended.h"


BinFileWithHashTable::BinFileWithHashTable(string fileName) : HashTable(5),
                                                              BinFileWork(std::move(fileName)) {
    dataToHash();
}

BinFileWithHashTable::BinFileWithHashTable(string fileName, int newFileSize) :
        HashTable(getOptimizedSize(newFileSize)), BinFileWork(std::move(fileName)) {
    fillBinFile(newFileSize);
    dataToHash();
}


void BinFileWithHashTable::dataToHash() {
    file.open(fileName, ios::in | ios::binary);

    if (!file.is_open()) {
        cout << "Error while opening file!" << endl;
        exit(0);
    }

    PhoneOwnerExtended phoneOwner{};
    file.read((char *) &phoneOwner, sizeof(PhoneOwnerExtended));
    int i = 0;
    while (!file.eof()) {
        if (!string(phoneOwner.phone).empty()) {
            HashTable::insert(phoneOwner.phone, i);
            i++;
        }
        file.read((char *) &phoneOwner, sizeof(PhoneOwnerExtended));
    }

    file.close();
}

PhoneOwnerExtended BinFileWithHashTable::find(const std::string &phoneNumber) {
    int position = HashTable::find(phoneNumber);
    return position == -1 ? PhoneOwnerExtended("", "", "") : getElement(position);
}

bool BinFileWithHashTable::insert(PhoneOwnerExtended phoneOwner, bool outIndexes) {

    if (HashTable::insert(phoneOwner.phone, getBusy(), outIndexes)) {
        BinFileWork::insert(phoneOwner, getBusy() - 1);
        return true;
    }

    return false;
}

bool BinFileWithHashTable::deleteElement(const string &phoneNumber) {

    int position = HashTable::deleteElement(phoneNumber);

    if (position == -1)
        return false;

    file.open(fileName, ios::in | ios::binary);
    file1.open("copy_" + fileName, ios::out | ios::binary);

    if (!(file.is_open() && file1.is_open())) {
        cout << "Error while opening file!" << endl;
        exit(0);
    }

    PhoneOwnerExtended phoneOwner;

    for (int i = 0; i < position; i++) {
        file.read((char *) &phoneOwner, sizeof(PhoneOwnerExtended));
        file1.write((char *) &phoneOwner, sizeof(PhoneOwnerExtended));
    }
    file.seekg((position + 1) * sizeof(PhoneOwnerExtended), ios::beg);
    for (int i = position + 1; i <= getBusy(); i++) {
        file.read((char *) &phoneOwner, sizeof(PhoneOwnerExtended));
        HashTable::reducePosition(phoneOwner.phone);
        file1.write((char *) &phoneOwner, sizeof(PhoneOwnerExtended));
    }
    file.close();
    file1.close();

    remove(fileName.c_str());
    rename(("copy_" + fileName).c_str(), fileName.c_str());

    return true;
}
