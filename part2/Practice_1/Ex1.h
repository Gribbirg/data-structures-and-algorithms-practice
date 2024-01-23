//
// Created by gribk on 08.09.2023.
//

#ifndef STRUCTURESANDALGORITHMSFORDATAPROCESSING_EX1_H
#define STRUCTURESANDALGORITHMSFORDATAPROCESSING_EX1_H

#include <iostream>
#include <iomanip>

using namespace std;

class Ex1 {

    static unsigned int setEvensToOne(unsigned int x);

    static unsigned int setSevenNineElevenToZero(unsigned int x);

    static unsigned int multiplyBySixteen(unsigned int x);

    static unsigned int divisionBySixteen(unsigned int x);

    static unsigned int setBitToZero(unsigned int x, unsigned int bitNum);

    static string getInBinary(unsigned int x);

    static void printAns(unsigned int before, unsigned int answer, bool afterEnter = true);

    static void exerciseOne(unsigned int(*fun)(unsigned int i));

public:

    static void start();

};


#endif //STRUCTURESANDALGORITHMSFORDATAPROCESSING_EX1_H
