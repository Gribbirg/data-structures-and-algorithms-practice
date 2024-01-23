//
// Created by gribk on 04.10.2023.
//

#ifndef STRUCTURESANDALGORITHMSFORDATAPROCESSING_EX3_3_H
#define STRUCTURESANDALGORITHMSFORDATAPROCESSING_EX3_3_H

#include <fstream>
#include <iostream>

using namespace std;

class Ex3_3 {
private:
    static void binTest(fstream &fstream1, fstream &fstream2, unsigned int testNum);
    static void binTestFind(fstream &fstream1, fstream &fstream2);
public:
    static void start();
};


#endif //STRUCTURESANDALGORITHMSFORDATAPROCESSING_EX3_3_H
