//
// Created by gribk on 22.09.2023.
//

#ifndef STRUCTURESANDALGORITHMSFORDATAPROCESSING_EX2_2_H
#define STRUCTURESANDALGORITHMSFORDATAPROCESSING_EX2_2_H

#include <fstream>
#include <iostream>
#include <string>
#include "PhoneOwner.h"

using namespace std;

class Ex2_2 {
private:
    static PhoneOwner *linearSearch(ifstream &ifstream1, const string &phoneNumber);

public:
    static void start(ifstream &binFile);
};


#endif //STRUCTURESANDALGORITHMSFORDATAPROCESSING_EX2_2_H
