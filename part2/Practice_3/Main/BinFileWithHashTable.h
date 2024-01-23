//
// Created by gribk on 02.10.2023.
//

#ifndef STRUCTURESANDALGORITHMSFORDATAPROCESSING_BINFILEWITHHASHTABLE_H
#define STRUCTURESANDALGORITHMSFORDATAPROCESSING_BINFILEWITHHASHTABLE_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "HashTable.h"
#include "../PhoneOwnerExtended.h"
#include "BinFileWork.h"

using namespace std;

class BinFileWithHashTable : public BinFileWork, public HashTable {
private:

    void dataToHash();

public:

    BinFileWithHashTable(string fileName);

    BinFileWithHashTable(string fileName, int newFileSize);

    PhoneOwnerExtended find(const string &phoneNumber);

    bool insert(PhoneOwnerExtended phoneOwner, bool outIndexes = false);

    bool deleteElement(const string &phoneNumber);
};


#endif //STRUCTURESANDALGORITHMSFORDATAPROCESSING_BINFILEWITHHASHTABLE_H
