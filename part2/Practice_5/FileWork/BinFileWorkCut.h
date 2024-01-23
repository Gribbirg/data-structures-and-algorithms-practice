//
// Created by gribk on 04.10.2023.
//

#ifndef STRUCTURESANDALGORITHMSFORDATAPROCESSING_BINFILEWORK_H
#define STRUCTURESANDALGORITHMSFORDATAPROCESSING_BINFILEWORK_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "hashtable.h"
#include "../PhoneOwnerCut.h"

using namespace std;

class BinFileWorkCut {
private:

    void fillFileWithRandom(int count);

protected:
    fstream file;
    fstream file1;

public:
    BinFileWorkCut(string fileName);

    string fileName;

    void readAll();

    PhoneOwnerCut getElement(unsigned int position);

    void fillBinFile(int count);

    void fillBinFromEnter();

    void insert(PhoneOwnerCut phoneOwner, unsigned int position);

    void deleteElement(unsigned int position);
};


#endif //STRUCTURESANDALGORITHMSFORDATAPROCESSING_BINFILEWORK_H
