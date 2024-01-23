//
// Created by gribk on 02.10.2023.
//

#include "Practice3.h"
#include "Exercise/Ex3_2.h"
#include "Exercise/Ex3_3.h"

void Practice3::start() {
    cout << "Practice 3" << endl;
    cout << endl;

    unsigned int enter;
    fstream fstream1;
    fstream fstream2;

    while (true) {
        cout << "Enter exercise number or 0 for exit: ";
        cin >> enter;
        cout << endl;

        switch (enter) {

            case 0:
                cout << "Exit from practice 3" << endl;
                return;

            case 1:
                cout << "Exercise 1" << endl;
                cout << "Find it in report!" << endl;
                cout << endl;
                break;

            case 2:
                cout << "Exercise 2" << endl;
                Ex3_2::start();
                cout << endl;
                break;

            case 3:
                cout << "Exercise 3" << endl;
                Ex3_3::start();
                cout << endl;
                break;

            default:
                cout << "Error. Try again!" << endl;
        }
        cout << endl;
    }
}
