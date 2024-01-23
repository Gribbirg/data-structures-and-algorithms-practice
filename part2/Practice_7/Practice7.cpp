//
// Created by gribk on 27.11.2023.
//

#include <algorithm>
#include <chrono>
#include "Practice7.h"

void Practice7::start() {
    cout << "Practice 7" << endl;
    cout << endl;

    int enter;
    string text;
    Practice7 object(0L);
    auto startTime = chrono::steady_clock::now();
    auto endTime = chrono::steady_clock::now();
    unsigned int ans;

    cout << "Information about operations numbers:" << endl
         << "0 - exit;" << endl
         << "1 - print information;" << endl
         << "2 - brute force method;" << endl
         << "3 - dynamic programming method;" << endl
         << "4 - comparison." << endl
         << endl;

    while (true) {
        cout << "Enter operation number or 0 for exit: ";
        cin >> enter;

        switch (enter) {

            case 0:
                cout << "Exit from practice 7" << endl;
                return;

            case 1:
                cout << "Information about operations numbers:" << endl
                     << "0 - exit;" << endl
                     << "1 - print information;" << endl
                     << "2 - brute force method;" << endl
                     << "3 - dynamic programming method;" << endl
                     << "4 - comparison." << endl;
                break;

            case 2:
                text = getLine();

                cout << "Brute force method:" << endl;
                object.counter = 0;
                startTime = chrono::steady_clock::now();
                ans = object.bruteForceMethod(text);
                endTime = chrono::steady_clock::now();
                cout << "Maximum palindrome length: " << ans << endl;
                cout << "Number of comparisons: " << object.counter << endl;
                cout << "Time: " << chrono::duration<double, milli>(endTime - startTime).count() << " milliseconds"
                     << endl;
                break;

            case 3:
                text = getLine();

                cout << "Dynamic programming method:" << endl;
                object.counter = 0;
                startTime = chrono::steady_clock::now();
                ans = object.dynamicProgrammingMethod(text);
                endTime = chrono::steady_clock::now();
                cout << "Maximum palindrome length: " << ans << endl;
                cout << "Number of comparisons: " << object.counter << endl;
                cout << "Time: " << chrono::duration<double, milli>(endTime - startTime).count() << " milliseconds"
                     << endl;
                break;

            case 4:
                text = getLine();
                cout << endl;

                cout << "Brute force method:" << endl;
                object.counter = 0;
                startTime = chrono::steady_clock::now();
                ans = object.bruteForceMethod(text);
                endTime = chrono::steady_clock::now();
                cout << "Maximum palindrome length: " << ans << endl;
                cout << "Number of comparisons: " << object.counter << endl;
                cout << "Time: " << chrono::duration<double, milli>(endTime - startTime).count() << " milliseconds"
                     << endl;

                cout << endl;

                cout << "Dynamic programming method:" << endl;
                object.counter = 0;
                startTime = chrono::steady_clock::now();
                ans = object.dynamicProgrammingMethod(text);
                endTime = chrono::steady_clock::now();
                cout << "Maximum palindrome length: " << ans << endl;
                cout << "Number of comparisons: " << object.counter << endl;
                cout << "Time: " << chrono::duration<double, milli>(endTime - startTime).count() << " milliseconds"
                     << endl;
                break;

            default:
                cout << "Error. Try again!" << endl;
        }
        cout << endl;
    }

}

string Practice7::getLine() {
    string text;
    cout << "Enter line or \"file\" to import from file: ";
    cin >> text;
    if (text == "file") {
        fstream fstream1;
        fstream1.open("enter.txt");
        fstream1 >> text;
        fstream1.close();
    }
    return text;
}

unsigned int Practice7::bruteForceMethod(const string &text) {
    if (check(text)) return text.length();
    string str;
    unsigned int maxLen = 0;
    for (int i = 0; i < text.length(); i++) {
        str = text;
        str.erase(i, 1);
        maxLen = max(maxLen, bruteForceMethod(str));
    }
    return maxLen;
}

bool Practice7::check(const string &text) {
    for (int i = 0; i < text.length() / 2; i++) {
        counter++;
        if (text[i] != text[text.length() - 1 - i])
            return false;
    }
    return true;
}

Practice7::Practice7(unsigned long long int counter) : counter(counter) {}

unsigned int Practice7::dynamicProgrammingMethod(const string &text) {
    int **matrix = new int *[text.length()];
    for (int i = 0; i < text.length(); i++) {
        matrix[i] = new int[i + 2];
        for (int j = 0; j < i; j++) {
            matrix[i][j] = -1;
        }
        matrix[i][i] = 1;
        matrix[i][i + 1] = 0;
    }
    auto ans = (unsigned int) dynamicProgrammingFind(text, matrix, (int) text.length() - 1, 0);
    for (int i = 0; i < text.length(); i++)
        delete[] matrix[i];
    delete[] matrix;
    return ans;
}

int Practice7::dynamicProgrammingFind(const string &text, int **matrix, int i, int j) {
    if (matrix[i][j] == -1) {
        counter++;
        if (text[i] == text[j])
            matrix[i][j] = dynamicProgrammingFind(text, matrix, i - 1, j + 1) + 2;
        else
            matrix[i][j] = max(dynamicProgrammingFind(text, matrix, i, j + 1),
                               dynamicProgrammingFind(text, matrix, i - 1, j));
    }
    return matrix[i][j];
}
