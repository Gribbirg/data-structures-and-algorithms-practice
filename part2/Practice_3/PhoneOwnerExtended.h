//
// Created by gribk on 02.10.2023.
//

#ifndef STRUCTURESANDALGORITHMSFORDATAPROCESSING_PHONEOWNEREXTENDED_H
#define STRUCTURESANDALGORITHMSFORDATAPROCESSING_PHONEOWNEREXTENDED_H


#include "../Practice_2/PhoneOwner.h"

struct PhoneOwnerExtended {
    char phone[19];
    char address[56];
    char fullName[42];

    string to_string();

    static unsigned long long int phoneToLong(string phone);

    static string getRandomPhoneNumber(int i);

    static string getRandomAddress(int i);

    static string getRandomFullName(int i);

    static PhoneOwnerExtended getRandomOwner(int i);

private:
    static int getRandom(unsigned int i);

public:
    PhoneOwnerExtended();

    PhoneOwnerExtended(const string& phone, int i);

    PhoneOwnerExtended(const string& phone, const string& address, const string& fullName);
};


#endif //STRUCTURESANDALGORITHMSFORDATAPROCESSING_PHONEOWNEREXTENDED_H
