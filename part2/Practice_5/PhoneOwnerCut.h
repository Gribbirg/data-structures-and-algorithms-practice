//
// Created by gribk on 29.10.2023.
//

#ifndef STRUCTURESANDALGORITHMSFORDATAPROCESSING_PHONEOWNERCUT_H
#define STRUCTURESANDALGORITHMSFORDATAPROCESSING_PHONEOWNERCUT_H

#include <string>

using namespace std;

struct PhoneOwnerCut {
    char phone[19];
    char address[56];
    string to_string();

    static unsigned long long int phoneToLong(string phone);

    static string getRandomPhoneNumber();

    static string getRandomAddress();

    static PhoneOwnerCut getRandomOwner();

    PhoneOwnerCut();

    PhoneOwnerCut(const string& phone);

    PhoneOwnerCut(const string& phone, const string& address);

private:
    static string getRandomNum(int maxValue);

};


#endif //STRUCTURESANDALGORITHMSFORDATAPROCESSING_PHONEOWNERCUT_H
