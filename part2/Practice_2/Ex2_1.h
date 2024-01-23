//
// Created by gribk on 20.09.2023.
//

#ifndef STRUCTURESANDALGORITHMSFORDATAPROCESSING_EX2_1_H
#define STRUCTURESANDALGORITHMSFORDATAPROCESSING_EX2_1_H

#include "iostream"
#include <vector>

using namespace std;

class Ex2_1 {
private:

    static int getRandom(unsigned int i);

    static void fillFileWithRandom(ofstream &enterFile);

    static string getPhoneNumber(int i);

    static string getRandomAddress(int i);

    static void dataToBin(ifstream &enterFile, ofstream &binFile);

    static void readBin(ifstream &binFileRead);

public:
    static void start(ofstream &ofstream1, ifstream &ifstream1);
};


#endif //STRUCTURESANDALGORITHMSFORDATAPROCESSING_EX2_1_H
