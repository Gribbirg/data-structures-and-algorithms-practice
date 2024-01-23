//
// Created by gribk on 08.09.2023.
//

#include "Practice2.h"
#include "Ex2_1.h"
#include "Ex2_2.h"
#include "Ex2_3.h"
#include <fstream>

void Practice2::start() {
    cout << "Practice 2" << endl;
    cout << endl;

    unsigned int enter;
    ofstream ofstream1;
    ifstream ifstream1;
    fstream fstream1;

    while (true) {
        cout << "Enter exercise number or 0 for exit: ";
        cin >> enter;
        cout << endl;

        switch (enter) {

            case 0:
                cout << "Exit from practice 2" << endl;
                return;

            case 1:
                cout << "Exercise 1" << endl;
                cout << endl;
                Ex2_1::start(ofstream1, ifstream1);
                break;

            case 2:
                cout << "Exercise 2" << endl;
                cout << endl;
                Ex2_2::start(ifstream1);
                break;

            case 3:
                cout << "Exercise 3" << endl;
                cout << endl;
                Ex2_3::start(fstream1);
                break;

            default:
                cout << "Error. Try again!" << endl;
        }
        cout << endl;
    }
}
