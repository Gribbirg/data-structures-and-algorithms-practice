//
// Created by gribk on 27.11.2023.
//

#ifndef STRUCTURESANDALGORITHMSFORDATAPROCESSING_PRACTICE7_H
#define STRUCTURESANDALGORITHMSFORDATAPROCESSING_PRACTICE7_H

#include "string"
#include "iostream"
#include "fstream"

using namespace std;

class Practice7 {
private:
    unsigned int bruteForceMethod(const string& text);
    unsigned int dynamicProgrammingMethod(const string& text);
    int dynamicProgrammingFind(const string& text, int **matrix, int i, int j);
    bool check(const string& text);
    unsigned long long int counter;
    explicit Practice7(unsigned long long int counter);
    static string getLine();
public:
    static void start();
};


#endif //STRUCTURESANDALGORITHMSFORDATAPROCESSING_PRACTICE7_H
