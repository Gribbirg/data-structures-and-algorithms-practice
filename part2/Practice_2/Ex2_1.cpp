//
// Created by gribk on 20.09.2023.
//

#include "Ex2_1.h"
#include "PhoneOwner.h"

#include <vector>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <cstring>

const string streets[] = {
        "Podkolzina street",
        "street named after Matan",
        "Muravyov Amursky St.",
        "Blyukhera street",
        "The street of the one who must not be named",
        "street A-18",
        "Dikoboltsina street",
        "Str. Initiative",
        "Ilya Avenue",
        "Tankovodsky Avenue",
        "Mushroom street",
        "Elevatorskaya street"
};

const unsigned int streetsSize = 12;

void Ex2_1::start(ofstream &ofstream1, ifstream &ifstream1) {
    unsigned int enter;

    fillFileWithRandom(ofstream1);

    dataToBin(ifstream1, ofstream1);

    cout << "Finish! Print bin data? (1 - yes, 0 - no): ";
    cin >> enter;
    if (enter) {
        cout << endl;
        readBin(ifstream1);
    }
}

// предусловие: наличие потока, удачное открытие файла, правильно введенное кол-во записей (>0)
// постусловие: созданный текстовый файл
void Ex2_1::fillFileWithRandom(ofstream &enterFile) {
    vector<string> numbers;
    unsigned int count;

    cout << "What count of phone owners?: ";
    cin >> count;

    string number;
    for (int i = 0; i < count; i++) {
        number = getPhoneNumber(i);

        while (binary_search(numbers.begin(), numbers.end(), number))
            number = getPhoneNumber(i);

        numbers.push_back(number);
    }

    cout << "Elements of file: " << numbers.size() << endl;

    shuffle(numbers.begin(), numbers.end(), std::mt19937(std::random_device()()));

    enterFile.open("enter.txt");
    if (enterFile.is_open()) {
        enterFile << numbers[0] << "\n" << getRandomAddress(0);
        for (int i = 1; i < count; i++) {
            enterFile << "\n" << numbers[i] << "\n" << getRandomAddress(i);
        }
    } else {
        cout << "Error while opening file!" << endl;
        exit(0);
    }
    enterFile.close();
}

int Ex2_1::getRandom(unsigned int i) {
    srand((unsigned) (time(nullptr) + i));
    return rand();
}

string Ex2_1::getPhoneNumber(int i) {
    string ans;
    int rand = getRandom(i << 0);
    ans += "+7 (" + to_string(rand % 10) + to_string(rand % 100 / 10) + to_string(rand % 1000 / 100) + ") ";
    rand = getRandom(i << 1);
    ans += to_string(rand % 10) + to_string(rand % 100 / 10) + to_string(rand % 1000 / 100) + "-";
    rand = getRandom(i << 2);
    ans += to_string(rand % 3) + to_string(rand % 100 / 10) + "-";
    rand = getRandom(i << 3);
    ans += to_string(rand % 10) + to_string(rand % 100 / 10);
    return ans;
}

string Ex2_1::getRandomAddress(int i) {
    return streets[getRandom(i * 8) % streetsSize] + " h. " + to_string(getRandom(i * 88) % 99 + 1) + " a. " +
           to_string(getRandom(i * 888) % 99 + 1);
}

// предусловие: наличие потока, удачное открытие файла, наличие записей в тестовом файле
// постусловие: созданный бинарный файл
void Ex2_1::dataToBin(ifstream &enterFile, ofstream &binFile) {
    enterFile.open("enter.txt");
    binFile.open("bin.dat", ios::out | ios::binary);

    if (!enterFile.is_open() || !binFile.is_open()) {
        cout << "Error while opening file!" << endl;
        exit(0);
    }

    PhoneOwner phoneOwner{};
    string phone;
    string address;

    while (!enterFile.eof()) {
        getline(enterFile, phone);
        getline(enterFile, address);

        strcpy(phoneOwner.phone, phone.c_str());
        strcpy(phoneOwner.address, address.c_str());

        binFile.write((char *) &phoneOwner, sizeof(PhoneOwner));
    }

    enterFile.close();
    binFile.close();
}

// предусловие: наличие потока, удачное открытие файла, наличие записей в бинарном файле
// постусловие: вывод записей из бинарного файла
void Ex2_1::readBin(ifstream &binFile) {
    binFile.open("bin.dat", ios::in | ios::binary);

    if (!binFile.is_open()) {
        cout << "Error while opening file!" << endl;
        exit(0);
    }

    PhoneOwner phoneOwner{};
    binFile.read((char *) &phoneOwner, sizeof(PhoneOwner));

    while (!binFile.eof()) {
        cout << phoneOwner.to_string() << endl;
        binFile.read((char *) &phoneOwner, sizeof(PhoneOwner));
    }

    binFile.close();
}

