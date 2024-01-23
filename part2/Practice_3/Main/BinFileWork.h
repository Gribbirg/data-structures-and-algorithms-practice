//
// Created by gribk on 04.10.2023.
//

#ifndef STRUCTURESANDALGORITHMSFORDATAPROCESSING_BINFILEWORK_H
#define STRUCTURESANDALGORITHMSFORDATAPROCESSING_BINFILEWORK_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "HashTable.h"
#include "../PhoneOwnerExtended.h"

using namespace std;

class BinFileWork {
private:

    void fillFileWithRandom(int count);

protected:
    fstream file;
    fstream file1;

public:
    BinFileWork(string fileName);

    string fileName;

    void readAll();

    PhoneOwnerExtended getElement(unsigned int position);

    void fillBinFile(int count);

    void fillBinFromEnter();

    void insert(PhoneOwnerExtended phoneOwner, unsigned int position);
};


#endif //STRUCTURESANDALGORITHMSFORDATAPROCESSING_BINFILEWORK_H
