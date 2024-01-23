//
// Created by gribk on 04.10.2023.
//

#include "BinFileWorkCut.h"

#include <utility>
#include <algorithm>
#include <cstring>
#include <random>

BinFileWorkCut::BinFileWorkCut(string fileName): fileName(std::move(fileName)) {}

void BinFileWorkCut::fillFileWithRandom(int count) {
    vector<string> numbers;

    string number;
    for (int i = 0; i < count; i++) {
        number = PhoneOwnerCut::getRandomPhoneNumber();

        while (binary_search(numbers.begin(), numbers.end(), number))
            number = PhoneOwnerCut::getRandomPhoneNumber();

        numbers.push_back(number);
    }

    shuffle(numbers.begin(), numbers.end(), std::mt19937(std::random_device()()));

    file.open("enter.txt", ios::out | ios::trunc);
    if (file.is_open()) {
        if (!numbers.empty()) {
            file << numbers[0] << "\n" << PhoneOwnerCut::getRandomAddress();
            for (int i = 1; i < count; i++) {
                file << "\n" << numbers[i] << "\n" << PhoneOwnerCut::getRandomAddress();
            }
        }
    } else {
        cout << "Error while opening file!" << endl;
        exit(0);
    }
    file.close();
}

void BinFileWorkCut::readAll() {
    cout << "Bin file:" << endl;
    file.open(fileName, ios::in | ios::binary);

    if (!file.is_open()) {
        cout << "Error while opening file!" << endl;
        exit(0);
    }

    PhoneOwnerCut phoneOwner{};
    file.read((char *) &phoneOwner, sizeof(PhoneOwnerCut));
    int i = 0;
    while (!file.eof()) {
        cout << i << ": " << phoneOwner.to_string() << endl;
        i++;
        file.read((char *) &phoneOwner, sizeof(PhoneOwnerCut));
    }
    file.close();
}

PhoneOwnerCut BinFileWorkCut::getElement(unsigned int position) {
    file.open(fileName, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "Error while opening file!" << endl;
        exit(0);
    }

    PhoneOwnerCut phoneOwner{};

    file.seekg(position * sizeof(PhoneOwnerCut), ios::beg);
    file.read((char *) &phoneOwner, sizeof(PhoneOwnerCut));

    file.close();

    return phoneOwner;
}

void BinFileWorkCut::fillBinFile(int count) {
    fillFileWithRandom(count);
    fillBinFromEnter();
}

void BinFileWorkCut::insert(PhoneOwnerCut phoneOwner, unsigned int position) {
    file.open(fileName, ios::out | ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "Error while opening file!" << endl;
        exit(0);
    }
    file.seekg(position * sizeof(PhoneOwnerCut), ios::beg);
    file.write((char *) &phoneOwner, sizeof(PhoneOwnerCut));
    file.close();
}

void BinFileWorkCut::fillBinFromEnter() {
    file1.open("enter.txt", ios::in);
    file.open(fileName, ios::out | ios::binary | ios::trunc);

    if (!file1.is_open() || !file.is_open()) {
        cout << "Error while opening file!" << endl;
        exit(0);
    }

    PhoneOwnerCut phoneOwner{};
    string phone;
    string address;

    while (!file1.eof()) {
        getline(file1, phone);
        getline(file1, address);

        strcpy(phoneOwner.phone, phone.c_str());
        strcpy(phoneOwner.address, address.c_str());

        file.write((char *) &phoneOwner, sizeof(PhoneOwnerCut));
    }

    file1.close();
    file.close();
}

void BinFileWorkCut::deleteElement(unsigned int position) {
    file.open(fileName, ios::in | ios::binary);
    file1.open("copy_" + fileName, ios::out | ios::binary);

    if (!(file.is_open() && file1.is_open())) {
        cout << "Error while opening file!" << endl;
        exit(0);
    }

    PhoneOwnerCut phoneOwner;

    for (int i = 0; i < position; i++) {
        file.read((char *) &phoneOwner, sizeof(PhoneOwnerCut));
        file1.write((char *) &phoneOwner, sizeof(PhoneOwnerCut));
    }
    file.seekg((position + 1) * sizeof(PhoneOwnerCut), ios::beg);
    file.read((char *) &phoneOwner, sizeof(PhoneOwnerCut));
    while (!file.eof()) {
        file1.write((char *) &phoneOwner, sizeof(PhoneOwnerCut));
        file.read((char *) &phoneOwner, sizeof(PhoneOwnerCut));
    }
    file.close();
    file1.close();

    remove(fileName.c_str());
    rename(("copy_" + fileName).c_str(), fileName.c_str());
}


