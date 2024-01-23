//
// Created by gribk on 08.09.2023.
//

#ifndef STRUCTURESANDALGORITHMSFORDATAPROCESSING_EX2_H
#define STRUCTURESANDALGORITHMSFORDATAPROCESSING_EX2_H


#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Ex2 {
    static unsigned char setOneToPosition(unsigned char x, unsigned int position);

    static vector<unsigned int> sortSizeEight(vector<unsigned int> mass);

    static vector<unsigned int> sortSizeSixtyFour(vector<unsigned int> mass);

    static vector<unsigned int> enterMass(unsigned int size, bool firstPart);

    static string massToLine(vector<unsigned int> mass);
public:
    static void start();
};


#endif //STRUCTURESANDALGORITHMSFORDATAPROCESSING_EX2_H
