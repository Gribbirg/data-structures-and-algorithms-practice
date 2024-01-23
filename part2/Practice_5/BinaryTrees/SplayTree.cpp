//
// Created by gribk on 30.10.2023.
//

#include "SplayTree.h"

bool SplayTree::insert(const string &phone, int position) {

    if (root == nullptr) {
        root = new NodeTree(phone, position);
        return true;
    }

    unsigned long long int phoneNum = PhoneOwnerCut::phoneToLong(phone);

    root = splay(root, phoneNum);

    if (root->value == phone)
        return false;

    auto node = new NodeTree(phone, position);

    if (phoneNum < PhoneOwnerCut::phoneToLong(root->value)) {
        node->rightNode = root;
        node->leftNode = root->leftNode;
        root->leftNode = nullptr;
    } else {
        node->leftNode = root;
        node->rightNode = root->rightNode;
        root->rightNode = nullptr;
    }
    root = node;
//    cout << rotationCount << endl;
    return true;
}

int SplayTree::deleteElement(const string &phone) {
    int position = find(phone);
    if (position != -1) {
        NodeTree *nodeDel = root;
        if (root->leftNode == nullptr && root->rightNode == nullptr) {
            root = nullptr;
        } else if (root->leftNode == nullptr) {
            root = root->rightNode;
        } else if (root->rightNode == nullptr) {
            root = root->leftNode;
        } else {
            NodeTree *node = root->rightNode;
            root = root->leftNode;
            root = splay(root, PhoneOwnerCut::phoneToLong(phone));
            root->rightNode = node;
        }
        nodeDel->del();
        root->reducePositions(position);
    }
    return position;
}

int SplayTree::find(const string &phone) {
    if (root == nullptr) return -1;

    root = splay(root, PhoneOwnerCut::phoneToLong(phone));

    return (root->value == phone) ? root->position : -1;
}

void SplayTree::print() {
    BinaryTree::print();
}

BinaryTree::NodeTree *SplayTree::leftRotation(BinaryTree::NodeTree *node) {
//    rotationCount++;
    NodeTree *child = node->rightNode;
    node->rightNode = child->leftNode;
    child->leftNode = node;
    return child;
}

BinaryTree::NodeTree *SplayTree::rightRotation(BinaryTree::NodeTree *node) {
//    rotationCount++;
    NodeTree *child = node->leftNode;
    node->leftNode = child->rightNode;
    child->rightNode = node;
    return child;
}

BinaryTree::NodeTree *SplayTree::splay(NodeTree *node, unsigned long long int phone) {
    if (node == nullptr || phone == PhoneOwnerCut::phoneToLong(node->value)) return node;

    if (phone < PhoneOwnerCut::phoneToLong(node->value)) {

        if (node->leftNode == nullptr) return node;

        if (phone < PhoneOwnerCut::phoneToLong(node->leftNode->value)) {

            node->leftNode->leftNode = splay(node->leftNode->leftNode, phone);
            node = rightRotation(node);

        } else if (phone > PhoneOwnerCut::phoneToLong(node->leftNode->value)) {

            node->leftNode->rightNode = splay(node->leftNode->rightNode, phone);
            if (node->leftNode->rightNode != nullptr)
                node->leftNode = leftRotation(node->leftNode);

        }

        return (node->leftNode == nullptr) ? node : rightRotation(node);

    } else {

        if (node->rightNode == nullptr) return node;

        if (phone < PhoneOwnerCut::phoneToLong(node->rightNode->value)) {

            node->rightNode->leftNode = splay(node->rightNode->leftNode, phone);
            if (node->rightNode->leftNode != nullptr)
                node->rightNode = rightRotation(node->rightNode);

        } else if (phone > PhoneOwnerCut::phoneToLong(node->rightNode->value)) {

            node->rightNode->rightNode = splay(node->rightNode->rightNode, phone);
            node = leftRotation(node);

        }

        return (node->rightNode == nullptr) ? node : leftRotation(node);

    }
}

SplayTree::~SplayTree() {
    delete root;
}
