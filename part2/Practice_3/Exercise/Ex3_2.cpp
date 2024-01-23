//
// Created by gribk on 04.10.2023.
//

#include "Ex3_2.h"
#include "../PhoneOwnerExtended.h"
#include "../Main//HashTable.h"

void Ex3_2::start() {
    fstream fstream1;
    int enter, i = 0;
    string phone;

    cout << "Enter table size: ";
    cin >> enter;
    cout << endl;

    HashTable hashTable(enter);

    cout << "Information about operations numbers:" << endl
         << "0 - exit from exercise 2;" << endl
         << "1 - print operations info;" << endl
         << "2 - print table;" << endl
         << "3 - export table to file;" << endl
         << "4 - find element;" << endl
         << "5 - insert element;" << endl
         << "6 - insert many random elements;" << endl
         << "7 - delete element;" << endl
         << "8 - update table;" << endl
         << "11 - test insert;" << endl
         << "12 - test insert with collision;" << endl
         << "13 - test insert with update table;" << endl
         << "14 - test delete element;" << endl
         << "15 - test find element;" << endl
         << "16 - test find element after deleted element." << endl
         << endl;

    while (true) {
        cout << "Enter operation number or 0 for exit: ";
        cin >> enter;
        cout << endl;

        switch (enter) {

            case 0:
                cout << "Exit from exercise 2" << endl;
                return;

            case 1:
                cout << "Information about operations numbers:" << endl
                     << "0 - exit from exercise 2;" << endl
                     << "1 - print operations info;" << endl
                     << "2 - print table;" << endl
                     << "3 - export table to file;" << endl
                     << "4 - find element;" << endl
                     << "5 - insert element;" << endl
                     << "6 - insert many random elements;" << endl
                     << "7 - delete element;" << endl
                     << "8 - update table;" << endl
                     << "11 - test insert;" << endl
                     << "12 - test insert with collision;" << endl
                     << "13 - test insert with update table;" << endl
                     << "14 - test delete element;" << endl
                     << "15 - test find element;" << endl
                     << "16 - test find element after deleted element." << endl;
                break;

            case 2:
                hashTable.printTable();
                break;

            case 3:
                hashTable.exportToFile(fstream1);
                cout << endl << "Done!" << endl;
                break;

            case 4:
                cout << "Enter the phone number you are looking for (format: +7 (XXX) XXX-XX-XX): ";
                while (getline(cin, phone) && phone.empty());
                cout << endl;

                enter = hashTable.find(phone);
                if (enter == -1)
                    cout << "The phone " << phone << " isn't in the table!" << endl;
                else
                    cout << "The position of phone " << phone << " is " << enter << endl;

                phone = "";
                break;

            case 5:
                cout
                        << "Enter the phone number you want to insert (format: +7 (XXX) XXX-XX-XX) or 0 to insert random: ";
                while (getline(cin, phone) && phone.empty());

                if (phone == "0") phone = PhoneOwnerExtended::getRandomPhoneNumber(i);

                cout << endl;
                if (hashTable.insert(phone, i, true)) {
                    cout << endl << "Phone " << phone << " is now in the table!" << endl;
                    i++;
                } else
                    cout << "Phone " << phone << " is already in the table!" << endl;

                break;

            case 6:

                cout << "How many elements you want to insert: ";
                cin >> enter;

                for (int j = 0; j < enter; j++) {
                    while (!hashTable.insert(PhoneOwnerExtended::getRandomPhoneNumber(i), i))
                        i++;
                    i++;
                }
                cout << "Done!" << endl;

                break;

            case 7:

                cout << "Enter the phone number you want to delete (format: +7 (XXX) XXX-XX-XX): ";
                while (getline(cin, phone) && phone.empty());

                cout << endl;
                if (hashTable.deleteElement(phone) != -1)
                    cout << "Phone " << phone << " was deleted!" << endl;
                else
                    cout << "Phone " << phone << " isn't in the table!" << endl;

                break;

            case 8:
                cout << "Enter new size of the table: ";
                cin >> enter;
                cout << endl;

                hashTable.update(enter);
                cout << "Done!" << endl;
                break;

            case 11:
                tableTest(1);
                break;

            case 12:
                tableTest(2);
                break;

            case 13:
                tableTest(3);
                break;

            case 14:
                tableTest(4);
                break;

            case 15:
                tableTest(5);
                break;

            case 16:
                tableTest(6);
                break;

            default:
                cout << "Error. Try again!" << endl;
        }
        cout << endl << endl;
    }
}

void Ex3_2::tableTest(unsigned int testNum) {
    HashTable testTable(10);
    testTable.insert("+7 (011) 331-07-07", 0);
    testTable.insert("+7 (790) 701-22-56", 1);
    testTable.insert("+7 (390) 001-11-93", 2);
    testTable.insert("+7 (090) 390-00-31", 3);
    testTable.insert("+7 (780) 780-28-78", 4);
    testTable.insert("+7 (311) 931-19-68", 5);

    cout << "Table before test: " << endl;
    testTable.printTable();

    cout << endl;
    switch (testNum) {
        case 1:
            cout << "Insert phone +7 (611) 641-20-22" << endl;
            testTable.insert("+7 (611) 641-20-22", 5, true);
            break;

        case 2:
            cout << "Insert with collision phone +7 (301) 021-15-81" << endl;
            testTable.insert("+7 (301) 021-15-81", 5, true);
            break;

        case 3:
            cout << "Insert with update table phones +7 (611) 641-20-22, +7 (301) 021-15-81"
                 << endl;
            testTable.insert("+7 (611) 641-20-22", 5);
            testTable.insert("+7 (301) 021-15-81", 6);
            break;

        case 4:
            cout << "Delete element +7 (390) 001-11-93" << endl;
            testTable.deleteElement("+7 (390) 001-11-93");
            break;

        case 5:
            cout << "Find element +7 (090) 390-00-31" << endl;
            cout << "Position of it: " << testTable.find("+7 (090) 390-00-31") << endl;
            break;

        case 6:
            cout << "Find element +7 (311) 931-19-68 after delete +7 (780) 780-28-78" << endl;
            testTable.deleteElement("+7 (780) 780-28-78");
            cout << "Position of it: " << testTable.find("+7 (311) 931-19-68") << endl;
            break;

    }
    cout << endl;

    cout << "Table after test: " << endl;
    testTable.printTable();
}
