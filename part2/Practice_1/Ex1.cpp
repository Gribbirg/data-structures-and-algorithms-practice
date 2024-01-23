//
// Created by gribk on 08.09.2023.
//

#include "Ex1.h"


unsigned int Ex1::setEvensToOne(unsigned int x) {
    return x | 0x55555555;
}

unsigned int Ex1::setSevenNineElevenToZero(unsigned int x) {
    return x & 0xFFFFF57F;
}

unsigned int Ex1::multiplyBySixteen(unsigned int x) {
    return x << 4;
}

unsigned int Ex1::divisionBySixteen(unsigned int x) {
    return x >> 4;
}

unsigned int Ex1::setBitToZero(unsigned int x, unsigned int bitNum) {
    unsigned int mask = 1;
    return x & (~(mask << bitNum));
}

string Ex1::getInBinary(unsigned int x) {
    int n = sizeof(int) * 8;
    unsigned mask = (1 << (n - 1));
    string ans;
    for (int i = 1; i <= n; i++) {
        ans += (to_string((x & mask) >> (n - i)));
        mask = mask >> 1;
    }
    return ans;
}

void Ex1::printAns(unsigned int before, unsigned int answer, bool afterEnter) {
    cout << setw(20 - afterEnter) << "Before: " << before << endl;
    cout << setw(20) << "In binary: " << getInBinary(before) << endl;
    cout << setw(20) << "Answer in binary: " << getInBinary(answer) << endl;
    cout << setw(20) << "Answer: " << answer << endl;
    cout << endl;
}

void Ex1::exerciseOne(unsigned int(*fun)(unsigned int i)) {
    unsigned int x;
    cout << "Enter start number: ";
    cin >> x;
    printAns(x, fun(x));
}

void Ex1::start() {

    cout << "Exercise 1" << endl;
    cout << endl;

    unsigned int x, bitNum;
    unsigned int enter;

    while (true) {
        cout << "Enter part number or 0 for back: ";
        cin >> enter;
        cout << endl;

        switch (enter) {
            case 0:
                cout << endl;
                return;

            case 1:
                cout << "Part 1" << endl;

                x = 0x1EE76D;
                printAns(x, setEvensToOne(x), false);
                break;

            case 2:
                cout << "Part 2" << endl;

                exerciseOne(setSevenNineElevenToZero);
                break;

            case 3:
                cout << "Part 3" << endl;

                exerciseOne(multiplyBySixteen);
                break;

            case 4:
                cout << "Part 4" << endl;

                exerciseOne(divisionBySixteen);
                break;

            case 5:
                cout << "Part 5" << endl;

                cout << "Enter start number: ";
                cin >> x;
                cout << "Enter bit number (from zero): ";
                cin >> bitNum;
                printAns(x, setBitToZero(x, bitNum));
                break;

            default:
                cout << "Error. Try again!";
        }
    }
}
