//
// Created by gribk on 02.10.2023.
//

#ifndef STRUCTURESANDALGORITHMSFORDATAPROCESSING_HASHTABLE_H
#define STRUCTURESANDALGORITHMSFORDATAPROCESSING_HASHTABLE_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "../FileWork/BinFileSearch.h"

using namespace std;

class HashTableSearch : public BinFileSearch::ISearchClass {
private:
    struct HashTableSearchRow {
        string phone;
        int position;
        bool free;
        bool deleted;

        HashTableSearchRow(string phone, int position);

        HashTableSearchRow();

        void print();
    };

    HashTableSearchRow *table;
    unsigned int size;
    unsigned int busy;

    static bool isEasy(unsigned long long int x);

    static unsigned int hesh(unsigned long long int phone, unsigned int size);

    static unsigned int biasHesh(unsigned long long int phone, unsigned int size);

    int findElement(const string& phone);

public:
    virtual ~HashTableSearch();

    HashTableSearch(unsigned int size = 5);

    bool insert(const string &phone, int position) override;

    int deleteElement(const string &phone) override;

    void update(unsigned int sizeNew);

    void print() override;

    void exportToFile(fstream &resultFile);

    int find(const string &phone) override;

    unsigned int getSize() const;

    unsigned int getBusy() const;

    static unsigned int getOptimizedSize(unsigned int busy);

    void reducePosition(int positionMin);
};


#endif //STRUCTURESANDALGORITHMSFORDATAPROCESSING_HASHTABLE_H
