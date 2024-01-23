//
// Created by gribk on 08.09.2023.
//

#include <random>
#include <algorithm>
#include "Ex2.h"


void Ex2::start() {

    cout << "Exercise 2" << endl;

    unsigned int enter;
    vector<unsigned int> mass;
    unsigned int size;

    while (true) {
        cout << "Enter part number or 0 for go back: ";
        cin >> enter;
        cout << endl;
        switch (enter) {

            case 0:

                cout << endl;
                return;

            case 1:
                cout << "Part 1" << endl;
                cout << "Enter mass size or 0 for autofill: ";
                cin >> size;
                mass = enterMass(size, true);

                cout << setw(20 - (size == 0)) << "Massive before: " << massToLine(mass) << endl;
                mass = sortSizeEight(mass);
                cout << setw(20) << "Massive after: " << massToLine(mass) << endl;

                break;

            case 2:
                cout << "Part 2" << endl;
                cout << "Enter mass size 0 for autofill: ";
                cin >> size;
                mass = enterMass(size, false);

                cout << setw(20 - (size == 0)) << "Massive before: " << massToLine(mass) << endl;
                mass = sortSizeSixtyFour(mass);
                cout << setw(20) << "Massive after: " << massToLine(mass) << endl;

                break;

            default:
                cout << "Error. Try again!";
        }

        cout << endl;

    }

}

string Ex2::massToLine(vector<unsigned int> mass) {
    string ans;
    if (mass.size() == 0) return "";
    for (int i = 0; i < mass.size(); i++)
        ans += to_string(mass[i]) + ' ';

    ans.pop_back();
    return ans;
}

vector<unsigned int> Ex2::enterMass(unsigned int size, bool firstPart) {
    vector<unsigned int> mass;
    if (size == 0) {
        if (firstPart)
            for (int i = 0; i < 8; i++) mass.push_back(i);
        else
            for (int i = 0; i < 64; i++) mass.push_back(i);
        shuffle(mass.begin(), mass.end(), std::mt19937(std::random_device()()));
    } else {
        unsigned int enter;
        cout << "Enter mass elements (quantity " << size << "):" << endl;
        for (int i = 0; i < size; i++) {
            cout << i << ":";
            cin >> enter;
            mass.push_back(enter);
        }
    }
    return mass;
}

vector<unsigned int> Ex2::sortSizeEight(vector<unsigned int> mass) {
    unsigned char isInMass = 0;
    unsigned int ansSize = 0;
    for (int i = 0; i < mass.size(); i++) {
        isInMass = setOneToPosition(isInMass, mass[i]);
    }
    int n = sizeof(unsigned char) * 8;
    unsigned mask = 1;
    for (int i = n; i >= 1; i--) {
        if (((isInMass & mask) >> (n - i)) == 1) {
            mass[ansSize] = n - i;
            ansSize++;
        }
        mask = mask << 1;
    }
    return mass;
}

unsigned char Ex2::setOneToPosition(unsigned char x, unsigned int position) {
    return x | (1 << position);
}

vector<unsigned int> Ex2::sortSizeSixtyFour(vector<unsigned int> mass) {
    unsigned char isInMass[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < mass.size(); i++) {
        isInMass[7 - (mass[i] / 8)] = setOneToPosition(isInMass[7 - (mass[i] / 8)], mass[i] % 8);
    }
    int n = sizeof(unsigned char) * 8;
    unsigned int mask;
    unsigned int ansSize = 0;
    for (int j = 7; j >= 0; j--) {
        mask = 1;
        for (int i = n; i >= 1; i--) {
            if ((isInMass[j] & mask) == mask) {
                mass[ansSize] = n - i + 8 * (7 - j);
                ansSize++;
            }
            mask = mask << 1;
        }
    }
    return mass;
}


