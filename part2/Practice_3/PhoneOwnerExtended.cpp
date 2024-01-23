//
// Created by gribk on 02.10.2023.
//

#include "PhoneOwnerExtended.h"
#include <ctime>
#include <random>
#include <cstring>
#include <iostream>

PhoneOwnerExtended::PhoneOwnerExtended() {}

PhoneOwnerExtended::PhoneOwnerExtended(const string &phone, int i) {
    strcpy(this->phone, phone.c_str());
    strcpy(this->address, PhoneOwnerExtended::getRandomAddress(i).c_str());
    strcpy(this->fullName, PhoneOwnerExtended::getRandomFullName(i).c_str());
}

PhoneOwnerExtended::PhoneOwnerExtended(const string &phone, const string &address, const string &fullName) {
    strcpy(this->phone, phone.c_str());
    strcpy(this->address, address.c_str());
    strcpy(this->fullName, fullName.c_str());
}

PhoneOwnerExtended PhoneOwnerExtended::getRandomOwner(int i) {
    return PhoneOwnerExtended(getRandomPhoneNumber(i), getRandomAddress(i), getRandomFullName(i));
}

string PhoneOwnerExtended::to_string() {
    return "Phone owner: phone - " + string(phone) + "; address - " + string(address) + "; full name - " +
           string(fullName) + ".";
}

unsigned long long int PhoneOwnerExtended::phoneToLong(string phone) {
    return stoll(string({
                                phone[4],
                                phone[5],
                                phone[6],
                                phone[9],
                                phone[10],
                                phone[11],
                                phone[13],
                                phone[14],
                                phone[16],
                                phone[17]
                        }));
}

int PhoneOwnerExtended::getRandom(unsigned int i) {
    srand((unsigned) (time(nullptr) + i));
    return rand();
}

string PhoneOwnerExtended::getRandomPhoneNumber(int i) {
    string ans;
    int rand = getRandom(i << 0);
    ans += "+7 (" + std::to_string(rand % 10) + std::to_string(rand % 100 / 10) + std::to_string(rand % 1000 / 100) +
           ") ";
    rand = getRandom(i << 1);
    ans += std::to_string(rand % 10) + std::to_string(rand % 100 / 10) + std::to_string(rand % 1000 / 100) + "-";
    rand = getRandom(i << 2);
    ans += std::to_string(rand % 3) + std::to_string(rand % 100 / 10) + "-";
    rand = getRandom(i << 3);
    ans += std::to_string(rand % 10) + std::to_string(rand % 100 / 10);
    return ans;
}

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

const string surnames[]{
        "Abdeeva",
        "Voronin",
        "Gribkov",
        "Grigoriev",
        "Ermakov",
        "Zharikov",
        "Zholobov",
        "Kazakov",
        "Kazachenko",
        "Klimkin",
        "Kozhnev",
        "Kulikov",
        "Lastin",
        "Martynov",
        "Morozov",
        "Orlov",
        "Pankratova",
        "Parkhomenko",
        "Permilovskaya",
        "Polyansky",
        "Revenko",
        "Savchuk",
        "Trusov",
        "Usachev",
        "Usov",
        "Ustinov",
        "Tsvetkov",
        "Chakryan",
        "Shkarupa",
        "Yakovchuk"
};
const unsigned int surnamesSize = 30;

const string names[]{
        "Alisa",
        "Egor",
        "Alexander",
        "Alexey",
        "Kirill",
        "Nikolay",
        "Igor",
        "Vladimir",
        "Stepan",
        "Mikhail",
        "Sergey",
        "Vladislav",
        "Vasily",
        "Ilya",
        "Konstantin",
        "Anna",
        "Georgy",
        "Marianna",
        "Vyacheslav",
        "Maxim",
        "Semyon",
        "Oleg",
        "Rudolf",
        "Daria",
        "Alexandra"
};
const unsigned int namesSize = 25;


const string fatherNames[]{
        "Renatovna",
        "Yurievich",
        "Sergeevich",
        "Alexandrovich",
        "Romanovich",
        "Pavlovich",
        "Andreevich",
        "Olegovich",
        "Vadimovich",
        "Dmitrievich",
        "Ilyich",
        "Borisovich",
        "Konstantinovna",
        "Evgenievna",
        "Leonidovich",
        "Vyacheslavovich",
        "Ashotovich",
        "Vyacheslavovna"
};
const unsigned int fatherNamesSize = 18;

string PhoneOwnerExtended::getRandomAddress(int i) {
    return streets[getRandom(i * 8) % streetsSize] + " h. " + std::to_string(getRandom(i * 88) % 99 + 1) + " a. " +
           std::to_string(getRandom(i * 888) % 99 + 1);
}

string PhoneOwnerExtended::getRandomFullName(int i) {
    return surnames[getRandom(i * 12) % surnamesSize] + " " + names[getRandom(i * 12 * 12) % namesSize] + " " +
           fatherNames[getRandom(i * 12 * 12 * 12) % fatherNamesSize];
}


