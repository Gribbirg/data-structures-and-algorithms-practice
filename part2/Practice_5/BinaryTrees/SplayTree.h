//
// Created by gribk on 30.10.2023.
//

#ifndef STRUCTURESANDALGORITHMSFORDATAPROCESSING_SPLAYTREE_H
#define STRUCTURESANDALGORITHMSFORDATAPROCESSING_SPLAYTREE_H

#include "BinaryTree.h"
#include "../FileWork/BinFileSearch.h"
#include "../PhoneOwnerCut.h"

class SplayTree : public BinaryTree, public BinFileSearch::ISearchClass {
private:
    static NodeTree *leftRotation(NodeTree *node);

    static NodeTree *rightRotation(NodeTree *node);

    static NodeTree *splay(NodeTree *node, unsigned long long int phone);

//     unsigned int rotationCount = 0;
public:
    bool insert(const string &phone, int position) override;

    int deleteElement(const string &phone) override;

    int find(const string &phone) override;

    void print() override;

    ~SplayTree() override;
};


#endif //STRUCTURESANDALGORITHMSFORDATAPROCESSING_SPLAYTREE_H
