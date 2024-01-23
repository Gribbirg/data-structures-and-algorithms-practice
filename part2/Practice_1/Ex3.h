//
// Created by gribk on 08.09.2023.
//

#ifndef STRUCTURESANDALGORITHMSFORDATAPROCESSING_EX3_H
#define STRUCTURESANDALGORITHMSFORDATAPROCESSING_EX3_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

class Ex3 {

    static void fillFileWithRandom();

    static unsigned int getRandom(unsigned int i);

    static void printBinMass(vector<unsigned char> mass);

    static string getInBinary(unsigned char x);

public:
    static void start();
};


#endif //STRUCTURESANDALGORITHMSFORDATAPROCESSING_EX3_H
