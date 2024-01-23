//
// Created by gribk on 16.10.2023.
//

#include "PerfectlyBalancedBinaryTree.h"

PerfectlyBalancedBinaryTree::PerfectlyBalancedBinaryTree(vector<char> &values) {
    if (!values.empty())
        root = new Node(values);
    else
        root = nullptr;
}

void PerfectlyBalancedBinaryTree::print() {
    cout << "Tree:" << endl;

    queue<Node *> order;
    order.push(root);
    int height = 0;
    int maxHeight = getHeight();
    int indentation = ((int) pow(2, maxHeight) * 2 - 1);
    int lenElCount = 1;

    while (height < maxHeight) {

        cout << string((indentation - 1) / 2, ' ');

        for (int i = 0; i < lenElCount - 1; i++)
            outAndUpdateOrder(order, string(indentation, ' '));

        outAndUpdateOrder(order, string((indentation - 1) / 2, ' '));
        cout << endl;

        height++;
        indentation /= 2;
        lenElCount *= 2;
    }
}

void PerfectlyBalancedBinaryTree::outAndUpdateOrder(queue<Node *> &order, const string &out) {
    if (order.front() == nullptr)
        cout << ' ';
    else {
        cout << order.front()->value;
        order.push(order.front()->leftNode);
        order.push(order.front()->rightNode);
    }
    order.pop();
    cout << out;
}

PerfectlyBalancedBinaryTree::~PerfectlyBalancedBinaryTree() {
    delete root;
}

char PerfectlyBalancedBinaryTree::Node::getMostLeftNode() {
    return (leftNode == nullptr) ? value : leftNode->getMostLeftNode();
}

char PerfectlyBalancedBinaryTree::getMostLeftNode() {
    return (root == nullptr)? ' ' : root->getMostLeftNode();
}

int PerfectlyBalancedBinaryTree::getPathLengthToNode(char value) {

    if (root == nullptr) return -1;

    queue<Node *> order;
    Node *node;
    order.push(root);
    int len = 0;

    while (!order.empty()) {
        len++;
        node = order.front();
        order.pop();

        if (node->value == value)
            return (int) log2(len);

        if (node->leftNode != nullptr) order.push(node->leftNode);
        if (node->rightNode != nullptr) order.push(node->rightNode);
    }
    return -1;
}

char PerfectlyBalancedBinaryTree::getBiggestLeaf() {
    return (root == nullptr)? ' ' : root->getBiggestLeaf();
}

int PerfectlyBalancedBinaryTree::getHeight() {
    return (root == nullptr)? 0 : root->getHeight(1);
}

int PerfectlyBalancedBinaryTree::Node::getHeight(int height) {
    if (leftNode != nullptr && rightNode != nullptr)
        return max(leftNode->getHeight(height + 1), rightNode->getHeight(height + 1));
    if (leftNode != nullptr)
        return leftNode->getHeight(height + 1);
    if (rightNode != nullptr)
        return rightNode->getHeight(height + 1);
    return height;
}


char PerfectlyBalancedBinaryTree::Node::getBiggestLeaf() {
    if (leftNode != nullptr && rightNode != nullptr)
        return max(leftNode->getBiggestLeaf(), rightNode->getBiggestLeaf());
    if (leftNode != nullptr)
        return leftNode->getBiggestLeaf();
    if (rightNode != nullptr)
        return rightNode->getBiggestLeaf();
    return value;
}

PerfectlyBalancedBinaryTree::Node::Node(vector<char> &values) {

    this->value = values[0];

    vector<char> valLeft = vector<char>(values.begin() + 1, values.begin() + 1 + (int) values.size() / 2);
    vector<char> valRight = vector<char>(values.begin() + 1 + (int) valLeft.size(), values.end());

    leftNode = valLeft.empty() ? nullptr : new Node(valLeft);
    rightNode = valRight.empty() ? nullptr : new Node(valRight);

}

PerfectlyBalancedBinaryTree::Node::~Node() {
    delete leftNode;
    delete rightNode;
}
