//
// Created by gribk on 04.10.2023.
//

#include "BinFileWork.h"

#include <utility>
#include <algorithm>
#include <cstring>
#include <random>

BinFileWork::BinFileWork(string fileName): fileName(std::move(fileName)) {}

void BinFileWork::fillFileWithRandom(int count) {
    vector<string> numbers;

    string number;
    for (int i = 0; i < count; i++) {
        number = PhoneOwnerExtended::getRandomPhoneNumber(i);

        while (binary_search(numbers.begin(), numbers.end(), number))
            number = PhoneOwnerExtended::getRandomPhoneNumber(i);

        numbers.push_back(number);
    }

    shuffle(numbers.begin(), numbers.end(), std::mt19937(std::random_device()()));

    file.open("enter.txt", ios::out | ios::trunc);
    if (file.is_open()) {
        if (!numbers.empty()) {
            file << numbers[0] << "\n" << PhoneOwnerExtended::getRandomAddress(0) << "\n"
                 << PhoneOwnerExtended::getRandomFullName(0);
            for (int i = 1; i < count; i++) {
                file << "\n" << numbers[i] << "\n" << PhoneOwnerExtended::getRandomAddress(i) << "\n"
                     << PhoneOwnerExtended::getRandomFullName(i);
            }
        }
    } else {
        cout << "Error while opening file!" << endl;
        exit(0);
    }
    file.close();
}

void BinFileWork::readAll() {
    file.open(fileName, ios::in | ios::binary);

    if (!file.is_open()) {
        cout << "Error while opening file!" << endl;
        exit(0);
    }

    PhoneOwnerExtended phoneOwner{};
    file.read((char *) &phoneOwner, sizeof(PhoneOwnerExtended));
    int i = 0;
    while (!file.eof()) {
        cout << i << ": " << phoneOwner.to_string() << endl;
        i++;
        file.read((char *) &phoneOwner, sizeof(PhoneOwnerExtended));
    }
    file.close();
}

PhoneOwnerExtended BinFileWork::getElement(unsigned int position) {
    file.open(fileName, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "Error while opening file!" << endl;
        exit(0);
    }

    PhoneOwnerExtended phoneOwner{};

    file.seekg(position * sizeof(PhoneOwnerExtended), ios::beg);
    file.read((char *) &phoneOwner, sizeof(PhoneOwnerExtended));

    file.close();

    return phoneOwner;
}

void BinFileWork::fillBinFile(int count) {
    fillFileWithRandom(count);
    fillBinFromEnter();
}

void BinFileWork::insert(PhoneOwnerExtended phoneOwner, unsigned int position) {
    file.open(fileName, ios::out | ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "Error while opening file!" << endl;
        exit(0);
    }
    file.seekg(position * sizeof(PhoneOwnerExtended), ios::beg);
    file.write((char *) &phoneOwner, sizeof(PhoneOwnerExtended));
    file.close();
}

void BinFileWork::fillBinFromEnter() {
    file1.open("enter.txt", ios::in);
    file.open(fileName, ios::out | ios::binary | ios::trunc);

    if (!file1.is_open() || !file.is_open()) {
        cout << "Error while opening file!" << endl;
        exit(0);
    }

    PhoneOwnerExtended phoneOwner{};
    string phone;
    string address;
    string fullName;

    while (!file1.eof()) {
        getline(file1, phone);
        getline(file1, address);
        getline(file1, fullName);

        strcpy(phoneOwner.phone, phone.c_str());
        strcpy(phoneOwner.address, address.c_str());
        strcpy(phoneOwner.fullName, fullName.c_str());

        file.write((char *) &phoneOwner, sizeof(PhoneOwnerExtended));
    }

    file1.close();
    file.close();
}


