//
// Created by gribk on 10.11.2023.
//

#ifndef STRUCTURESANDALGORITHMSFORDATAPROCESSING_PRACTICE6_H
#define STRUCTURESANDALGORITHMSFORDATAPROCESSING_PRACTICE6_H

#include <iostream>
#include "MatrixGraph.h"

using namespace std;

class Practice6 {
private:
    static MatrixGraph *createGraph();
    static void insertEdges(MatrixGraph *graph);
public:
    static void start();
};


#endif //STRUCTURESANDALGORITHMSFORDATAPROCESSING_PRACTICE6_H
