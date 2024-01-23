//
// Created by gribk on 22.09.2023.
//

#include "Ex2_2.h"


void Ex2_2::start(ifstream &ifstream1) {

    string phoneNumber;
    cout << "Enter the phone number you are looking for (format: +7 (XXX) XXX-XX-XX): ";
    while (getline(cin, phoneNumber) && phoneNumber.empty());

    cout << endl;

    time_t startTime = clock();
    PhoneOwner *phoneOwner = linearSearch(ifstream1, phoneNumber);
    time_t endTime = clock();

    if (phoneOwner)
        cout << phoneOwner->to_string() << endl;
    else
        cout << "Number " << phoneNumber << " is not founded" << endl;

    cout << "Time spent: " << (double) (endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
}

// предусловие: наличие потока, удачное открытие файла
// постусловие: информация о записи по ключу или данные об её отсутствии
PhoneOwner* Ex2_2::linearSearch(ifstream &binFile, const string& phoneNumber) {

    binFile.open("bin.dat", ios::in | ios::binary);

    if (!binFile.is_open()) {
        cout << "Error while opening file!" << endl;
        exit(0);
    }

    auto *phoneOwner = new PhoneOwner();
    binFile.read((char *) &(*phoneOwner), sizeof(PhoneOwner));

    while (!binFile.eof()) {

        if (phoneOwner->phone == phoneNumber) {
            binFile.close();
            return phoneOwner;
        }

        binFile.read((char *) &(*phoneOwner), sizeof(PhoneOwner));
    }

    binFile.close();
    return nullptr;
}
