//
// Created by gribk on 29.10.2023.
//

#include "PhoneOwnerCut.h"
#include <ctime>
#include <random>
#include <cstring>

PhoneOwnerCut::PhoneOwnerCut() {}

PhoneOwnerCut::PhoneOwnerCut(const string &phone) {
    strcpy(this->phone, phone.c_str());
    strcpy(this->address, PhoneOwnerCut::getRandomAddress().c_str());
}

PhoneOwnerCut::PhoneOwnerCut(const string &phone, const string &address) {
    strcpy(this->phone, phone.c_str());
    strcpy(this->address, address.c_str());
}

PhoneOwnerCut PhoneOwnerCut::getRandomOwner() {
    return {getRandomPhoneNumber(), getRandomAddress()};
}

string PhoneOwnerCut::to_string() {
    return "Phone owner: phone - " + string(phone) + "; address - " + string(address) + ".";
}

unsigned long long int PhoneOwnerCut::phoneToLong(string phone) {
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

string PhoneOwnerCut::getRandomNum(int maxValue) {
    return std::to_string(rand() % maxValue);
}

string PhoneOwnerCut::getRandomPhoneNumber() {
    return "+7 (" + getRandomNum(10) + getRandomNum(10) + getRandomNum(10) + ") "
           + getRandomNum(10) + getRandomNum(10) + getRandomNum(10)
           + "-" + getRandomNum(10) + getRandomNum(10) + "-"
           + getRandomNum(10) + getRandomNum(10);
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
        "Elevatorskaya street",
        "Shkebedi street",
        "The street named after SiAOD",
        "Petyxovskay street",
        "Han street"
};
const unsigned int streetsSize = 16;

string PhoneOwnerCut::getRandomAddress() {
    return streets[rand() % streetsSize] + " h. " + std::to_string(rand() % 99 + 1) + " a. " +
           std::to_string(rand() % 99 + 1);
}



