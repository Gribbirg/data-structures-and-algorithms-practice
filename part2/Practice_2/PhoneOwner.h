//
// Created by gribk on 21.09.2023.
//

#ifndef STRUCTURESANDALGORITHMSFORDATAPROCESSING_PHONEOWNER_H
#define STRUCTURESANDALGORITHMSFORDATAPROCESSING_PHONEOWNER_H

#include <string>

using namespace std;

struct PhoneOwner {
    char phone[19];
    char address[56];
    string to_string();
};


#endif //STRUCTURESANDALGORITHMSFORDATAPROCESSING_PHONEOWNER_H
