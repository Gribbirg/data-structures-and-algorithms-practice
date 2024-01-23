//
// Created by gribk on 08.09.2023.
//

#include "Ex3.h"
#include <random>
#include <ctime>

void Ex3::start() {
    cout << "Exercise 3" << endl;
    cout << endl;

    unsigned int enter;
    bool printIsInMass;
    cout << "Create a new file? 1 - yes, 0 - no: ";
    cin >> enter;

    if (enter) fillFileWithRandom();

    cout << "Print full bit mass? 1 - yes, 0 - no: ";
    cin >> printIsInMass;

    time_t startTime = clock();

    vector<unsigned char> isInMass;
    isInMass.push_back(0);
    ifstream enterFile("enter.txt");
    if (!enterFile.is_open()) {
        cout << "Error while opening file!" << endl;
        exit(0);
    }
    unsigned int position;

    while (enterFile >> enter) {
        position = enter / 8;
        while (position > isInMass.size() - 1) {
            isInMass.push_back(0);
        }

        isInMass[position] = isInMass[position] | (1 << (enter % 8));

    }

    enterFile.close();
    if (printIsInMass) printBinMass(isInMass);

    ofstream resultFile("result.txt");
    if (!resultFile.is_open()) {
        cout << "Error while opening file!" << endl;
        exit(0);
    }
    unsigned int mask;
    int n = sizeof(unsigned char) * 8;
    for (int i = 0; i < isInMass.size(); i++) {
        mask = 1;
        for (int j = n; j >= 1; j--) {
            if ((isInMass[i] & mask) == mask) {
                resultFile << n - j + 8 * i << ' ';
            }
            mask <<= 1;
        }
    }
    resultFile.close();

    time_t endTime = clock();
    cout << endl;
    cout << "Sort end!" << endl;
    cout << "Time spent: " << (double) (endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
    unsigned int memory = isInMass.size();
    cout << "Memory spent: ";
    if (memory < 1024) cout << memory << " B";
    else if (memory < 1024 * 1024) cout << memory / 1024.0 << " KB";
    else cout << memory / (1024 * 1024.0) << " MB";
    cout << endl;

    cout << endl;
}

void Ex3::printBinMass(vector<unsigned char> mass) {
    cout << "Bit mass: " << endl;
    for (int i = 0; i < mass.size(); i++) {
        cout << setw(7) << i << ": " << getInBinary(mass[i]) << endl;
    }
}

void Ex3::fillFileWithRandom() {
    vector<unsigned int> numbers;
    unsigned int percentage, count;

    cout << "What percentage of numbers?: ";
    cin >> percentage;

    cout << "What count of numbers?: ";
    cin >> count;

    for(unsigned int i = 0; i < pow(10, 7); i++) {
        if (getRandom(i) % 100 < percentage) {
            numbers.push_back(i);
            if (numbers.size() == count) break;
        }
    }
    cout << "Elements of file: " << numbers.size() << endl;

    shuffle(numbers.begin(), numbers.end(), std::mt19937(std::random_device()()));

    ofstream enterFile("enter.txt");
    if (enterFile.is_open()) {
        for (unsigned int num: numbers) {
            enterFile << num << " ";
        }
    } else {
        cout << "Error while opening file!" << endl;
        exit(0);
    }
    enterFile.close();
}

unsigned int Ex3::getRandom(unsigned int i) {
    srand((unsigned) (time(NULL) + i * 8));
    return rand();
}

string Ex3::getInBinary(unsigned char x) {
    int n = sizeof(unsigned char) * 8;
    unsigned mask = (1 << (n - 1));
    string ans;
    for (int i = 1; i <= n; i++) {
        ans += (to_string((x & mask) >> (n - i)));
        mask = mask >> 1;
    }
    return ans;
}


