//
// Created by gribk on 08.09.2023.
//

#include "Pr1.h"

void Pr1::start() {
    cout << "Practice 1" << endl;
    cout << endl;

    unsigned int enter;

    while (true) {
        cout << "Enter exercise number or 0 for exit: ";
        cin >> enter;
        cout << endl;

        switch (enter) {

            case 0:
                cout << "Exit from practice 1" << endl;
                cout << endl;
                return;

            case 1:
                Ex1::start();
                break;

            case 2:

                Ex2::start();
                break;

            case 3:

                Ex3::start();
                break;

            default:
                cout << "Error. Try again!" << endl;
        }
    }
}
