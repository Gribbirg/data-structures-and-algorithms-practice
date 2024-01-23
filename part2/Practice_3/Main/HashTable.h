//
// Created by gribk on 02.10.2023.
//

#ifndef STRUCTURESANDALGORITHMSFORDATAPROCESSING_HASHTABLE_H
#define STRUCTURESANDALGORITHMSFORDATAPROCESSING_HASHTABLE_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class HashTable {
private:
    struct HashTableRow {
        string phone;
        int position;
        bool free;
        bool deleted;

        HashTableRow(string phone, int position);

        HashTableRow();

        void print();
    };

    HashTableRow *table;
    unsigned int size;
    unsigned int busy;

    static bool isEasy(unsigned long long int x);

    static unsigned int hesh(unsigned long long int phone, unsigned int size);

    static unsigned int biasHesh(unsigned long long int phone, unsigned int size);

    int findElement(const string& phone);

public:
    virtual ~HashTable();

    HashTable(unsigned int size);

    bool insert(const string &phone, int position, bool outIndexes = false);

    int deleteElement(const string &phone);

    void update(unsigned int sizeNew);

    void printTable();

    void exportToFile(fstream &resultFile);

    int find(const string &phone);

    unsigned int getSize() const;

    unsigned int getBusy() const;

    static unsigned int getOptimizedSize(unsigned int busy);

    void reducePosition(const string& phone);
};


#endif //STRUCTURESANDALGORITHMSFORDATAPROCESSING_HASHTABLE_H
