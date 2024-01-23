//
// Created by gribk on 29.10.2023.
//

#include "BinaryTree.h"
#include "../PhoneOwnerCut.h"

#include <utility>

BinaryTree::NodeTree::~NodeTree() {
    delete rightNode;
    delete leftNode;
}

void BinaryTree::NodeTree::print(int level) {
    if (rightNode != nullptr) rightNode->print(level + 1);

    cout << string(level * 20, ' ') << value << " in " << position;
    if (leftNode != nullptr && rightNode != nullptr) cout << " X" << endl;
    else if (leftNode != nullptr) cout << R"( \)" << endl;
    else if (rightNode != nullptr) cout << " /" << endl;
    else cout << endl;

    if (leftNode != nullptr) leftNode->print(level + 1);
}

BinaryTree::NodeTree::NodeTree(string value, int position) : value(std::move(value)), position(position) {
    leftNode = nullptr;
    rightNode = nullptr;
}

void BinaryTree::NodeTree::reducePositions(int positionMin) {
    if (rightNode != nullptr) rightNode->reducePositions(positionMin);
    if (position > positionMin) position--;
    if (leftNode != nullptr) leftNode->reducePositions(positionMin);
}

void BinaryTree::NodeTree::del() {
    leftNode = nullptr;
    rightNode = nullptr;
    delete this;
}

void BinaryTree::print() {
    cout << "Binary tree:" << endl;
    if (root != nullptr) {
        root->print();
    } else {
        cout << endl;
    }
}

BinaryTree::BinaryTree() : root(nullptr) {}
