//
// Created by gribk on 22.09.2023.
//

#ifndef STRUCTURESANDALGORITHMSFORDATAPROCESSING_EX2_3_H
#define STRUCTURESANDALGORITHMSFORDATAPROCESSING_EX2_3_H

#include <fstream>
#include <vector>
#include "PhoneOwner.h"

using namespace std;

class Ex2_3 {
private:
    struct BinOffsetTablePow {
        string phone;
        unsigned int position;

        BinOffsetTablePow(string phone, unsigned int position);

        string to_string();

        bool operator<(const BinOffsetTablePow &rhs) const;
    };

    static vector<BinOffsetTablePow> generateBinOffsetTable(fstream &binFile);

    static void printBinOffsetTable(const vector<BinOffsetTablePow> &binOffsetTable);

    static vector<int> generateDelta(unsigned int size);

    static int
    binarySearch(const vector<BinOffsetTablePow> &binOffsetTable,
                 const vector<int> &delta,
                 const string &phone,
                 unsigned int i,
                 unsigned int j);

    static PhoneOwner getPhoneOwnerFromBin(fstream &binFile, int position);

public:
    static void start(fstream &fstream1);
};


#endif //STRUCTURESANDALGORITHMSFORDATAPROCESSING_EX2_3_H
