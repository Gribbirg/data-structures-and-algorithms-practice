//
// Created by gribk on 29.10.2023.
//

#include "BinarySearchTree.h"
#include "../PhoneOwnerCut.h"

bool BinarySearchTree::insert(const string &phone, int position) {
    if (root == nullptr) {
        root = new NodeTree(phone, position);
        return true;
    }
    return insert(root, phone, position);
}

int BinarySearchTree::deleteElement(const string &phone) {
    if (root != nullptr) {
        if (root->value == phone) {
            NodeTree *nodeForDel = root;
            root = findNewElement(nodeForDel);
            if (root != nullptr)
                root->reducePositions(nodeForDel->position);
            return nodeForDel->position;
        } else {
            return deleteElement(root, phone);
        }
    } else {
        return -1;
    }
}

int BinarySearchTree::deleteElement(BinaryTree::NodeTree *node, const string &phone) {

    NodeTree *nodeForDel;
    bool isLeft;

    if (PhoneOwnerCut::phoneToLong(phone) < PhoneOwnerCut::phoneToLong(node->value)) {
        nodeForDel = node->leftNode;
        isLeft = true;
    } else {
        nodeForDel = node->rightNode;
        isLeft = false;
    }

    if (nodeForDel == nullptr) return -1;

    if (nodeForDel->value == phone) {
        NodeTree *newChild = findNewElement(nodeForDel);
        nodeForDel->del();
        (isLeft) ? node->leftNode = newChild : node->rightNode = newChild;
        root->reducePositions(nodeForDel->position);
        return nodeForDel->position;
    } else {
        return deleteElement(nodeForDel, phone);
    }
}

BinaryTree::NodeTree *BinarySearchTree::findNewElement(BinaryTree::NodeTree *node) {
    NodeTree *newChild;

    if (node->leftNode != nullptr && node->leftNode != nullptr) {
        if (node->leftNode->rightNode != nullptr)
            newChild = cutMostRightChild(node->leftNode);
        else {
            newChild = node->leftNode;
            node->leftNode = newChild->leftNode;
        }
        newChild->leftNode = node->leftNode;
        newChild->rightNode = node->rightNode;
    } else if (node->leftNode != nullptr) {
        newChild = node->leftNode;
    } else if (node->rightNode != nullptr) {
        newChild = node->rightNode;
    } else {
        newChild = nullptr;
    }
    return newChild;
}

int BinarySearchTree::find(const string &phone) {
    return find(root, PhoneOwnerCut::phoneToLong(phone));
}

int BinarySearchTree::find(BinaryTree::NodeTree *node, unsigned long long int phone) {
    if (node == nullptr) return -1;

    unsigned long long int currentVal = PhoneOwnerCut::phoneToLong(node->value);
    if (phone < currentVal) return find(node->leftNode, phone);
    if (phone > currentVal) return find(node->rightNode, phone);
    return node->position;
}

void BinarySearchTree::print() {
    BinaryTree::print();
}

bool BinarySearchTree::insert(BinaryTree::NodeTree *node, const string &phone, int position) {
    if (PhoneOwnerCut::phoneToLong(phone) < PhoneOwnerCut::phoneToLong(node->value)) {
        if (node->leftNode != nullptr)
            return insert(node->leftNode, phone, position);
        else {
            node->leftNode = new NodeTree(phone, position);
            return true;
        }
    } else if (phone != node->value) {
        if (node->rightNode != nullptr)
            return insert(node->rightNode, phone, position);
        else {
            node->rightNode = new NodeTree(phone, position);
            return true;
        }
    }
    return false;
}

BinaryTree::NodeTree *BinarySearchTree::cutMostRightChild(BinaryTree::NodeTree *node) {
    if (node->rightNode->rightNode != nullptr)
        return cutMostRightChild(node->rightNode);

    NodeTree *nodeFind = node->rightNode;
    node->rightNode = nodeFind->leftNode;
    return nodeFind;
}

BinarySearchTree::~BinarySearchTree() {
    delete root;
}
