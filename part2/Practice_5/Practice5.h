//
// Created by gribk on 29.10.2023.
//

#ifndef STRUCTURESANDALGORITHMSFORDATAPROCESSING_PRACTICE5_H
#define STRUCTURESANDALGORITHMSFORDATAPROCESSING_PRACTICE5_H

#include "FileWork/BinFileSearch.h"

class Practice5 {
private:
    template<class T>
    static void withoutFile();

    template<class T>
    static void withFile();

    static void comparison();

    template<class T>
    static void test(const vector<string>& phones);

public:
    static void start();
};


#endif //STRUCTURESANDALGORITHMSFORDATAPROCESSING_PRACTICE5_H
