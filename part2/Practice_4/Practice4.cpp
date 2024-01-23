//
// Created by gribk on 16.10.2023.
//

#include "Practice4.h"


void Practice4::start() {
    cout << "Practice 4" << endl;
    cout << endl;

    unsigned int enter;
    char ch;

    PerfectlyBalancedBinaryTree *tree = createTree();
    cout << endl;

    cout << "Information about operations numbers:" << endl
         << "0 - exit;" << endl
         << "1 - print information;" << endl
         << "2 - create new tree;" << endl
         << "3 - print tree;" << endl
         << "4 - get value of most left node;" << endl
         << "5 - get path length to node with searched value;" << endl
         << "6 - get biggest value of leaf." << endl
         << endl;

    while (true) {
        cout << "Enter operation number or 0 for exit: ";
        cin >> enter;

        switch (enter) {

            case 0:
                cout << "Exit from practice 4" << endl;
                return;

            case 1:
                cout << "Information about operations numbers:" << endl
                     << "0 - exit;" << endl
                     << "1 - print information;" << endl
                     << "2 - create new tree;" << endl
                     << "3 - print tree;" << endl
                     << "4 - get value of most left node;" << endl
                     << "5 - get path length to node with searched value;" << endl
                     << "6 - get biggest value of leaf." << endl;
                break;

            case 2:
                delete tree;
                tree = createTree();
                break;

            case 3:
                tree->print();
                break;

            case 4:
                cout << "Most left value: " << tree->getMostLeftNode() << endl;
                break;

            case 5:
                cout << "Enter searched value: ";
                cin >> ch;
                enter = tree->getPathLengthToNode(ch);
                if (enter != -1)
                    cout << "Path length to '" << ch << "' = " << enter << endl;
                else
                    cout << "Char '" << ch << "' isn't in the tree!" << endl;
                break;

            case 6:
                cout << "Biggest value of leaf: " << tree->getBiggestLeaf() << endl;
                break;

            default:
                cout << "Error. Try again!" << endl;
        }
        cout << endl;
    }
}

PerfectlyBalancedBinaryTree *Practice4::createTree() {
    int n;
    bool random;
    cout << "How much elements?: ";
    cin >> n;
    cout << "Random values? (1 - yes, 0 - no): ";
    cin >> random;

    vector<char> values;
    char val;

    if (random) {
        for (int i = 0; i < n; i++) {
            srand((unsigned) (time(nullptr) * (i + 8)));
            values.push_back(rand() % 94 + 33);
        }
    } else {
        for (int i = 0; i < n; i++) {
            cout << i << ": ";
            cin >> val;
            values.push_back(val);
        }
    }
    auto *tree = new PerfectlyBalancedBinaryTree(values);
    tree->print();
    return tree;
}
