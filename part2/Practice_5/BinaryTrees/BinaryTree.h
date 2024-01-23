//
// Created by gribk on 29.10.2023.
//

#ifndef STRUCTURESANDALGORITHMSFORDATAPROCESSING_BINARYTREE_H
#define STRUCTURESANDALGORITHMSFORDATAPROCESSING_BINARYTREE_H

#include <string>
#include <iostream>

using namespace std;

class BinaryTree {
protected:
    struct NodeTree {
        string value;
        int position;
        NodeTree *leftNode;
        NodeTree *rightNode;

        NodeTree(string value, int position);

        ~NodeTree();

        void print(int level = 0);

        void reducePositions(int positionMin);

        void del();
    };

    NodeTree *root;
    BinaryTree();

public:

    void print();
};


#endif //STRUCTURESANDALGORITHMSFORDATAPROCESSING_BINARYTREE_H
