//
// Created by gribk on 04.10.2023.
//

#include "Ex3_3.h"
#include <cstring>
#include "../PhoneOwnerExtended.h"
#include "../Main/HashTable.h"
#include "../Main/BinFileWithHashTable.h"

void Ex3_3::start() {
    fstream fstream1;
    fstream fstream2;
    int enter;
    cout << "Create new file? (1 - yes, 0 - no): ";
    cin >> enter;
    cout << endl;
    BinFileWithHashTable *binHashTable;
    if (enter == 1) {
        cout << "Enter file size: ";
        cin >> enter;
        cout << endl;
        binHashTable = new BinFileWithHashTable("bin.dat", enter);
    } else {
        binHashTable = new BinFileWithHashTable("bin.dat");
    }
    cout << endl;

    string phone;
    string s;
    PhoneOwnerExtended phoneOwner;

    cout << "Information about operations numbers:" << endl
         << "0 - exit from exercise 3;" << endl
         << "1 - print operations info;" << endl
         << "2 - print hash table;" << endl
         << "3 - export table to file;" << endl
         << "4 - print data from bin file;" << endl
         << "5 - find element;" << endl
         << "6 - insert element;" << endl
         << "7 - insert many random elements;" << endl
         << "8 - delete element;" << endl
         << "11 - test insert;" << endl
         << "12 - test insert with collision;" << endl
         << "13 - test insert with update table;" << endl
         << "14 - test delete element;" << endl
         << "15 - test find element;" << endl
         << "16 - test find in file with size 1 000 000;" << endl
         << endl;

    while (true) {
        cout << "Enter operation number or 0 for exit: ";
        cin >> enter;
        cout << endl;

        switch (enter) {

            case 0:
                cout << "Exit from exercise 3" << endl;
                delete binHashTable;
                remove("bin_test.dat");
                return;

            case 1:
                cout << "Information about operations numbers:" << endl
                     << "0 - exit from exercise 3;" << endl
                     << "1 - print operations info;" << endl
                     << "2 - print hash table;" << endl
                     << "3 - export table to file;" << endl
                     << "4 - print data from bin file;" << endl
                     << "5 - find element;" << endl
                     << "6 - insert element;" << endl
                     << "7 - insert many random elements;" << endl
                     << "8 - delete element;" << endl
                     << "11 - test insert;" << endl
                     << "12 - test insert with collision;" << endl
                     << "13 - test insert with update table;" << endl
                     << "14 - test delete element;" << endl
                     << "15 - test find element;" << endl
                     << "16 - test find in file with size 1 000 000;" << endl;
                break;

            case 2:
                binHashTable->printTable();
                break;

            case 3:
                binHashTable->exportToFile(fstream1);
                cout << "Done" << endl;
                break;

            case 4:
                binHashTable->readAll();
                break;

            case 5:
                cout << "Enter the phone number you are looking for (format: +7 (XXX) XXX-XX-XX): ";
                while (getline(cin, phone) && phone.empty());
                cout << endl;

                phoneOwner = binHashTable->find(phone);
                if (phoneOwner.phone[0] == 0)
                    cout << "The phone " << phone << " isn't in the file!" << endl;
                else
                    cout << phoneOwner.to_string() << endl;

                phone = "";
                phoneOwner = PhoneOwnerExtended();
                break;

            case 6:
                cout
                        << "Enter the phone number you want to insert (format: +7 (XXX) XXX-XX-XX) or 0 to insert random: ";
                while (getline(cin, phone) && phone.empty());
                cout << endl;

                if (phone == "0") {
                    do {
                        phoneOwner = PhoneOwnerExtended::getRandomOwner(binHashTable->getBusy());
                    } while (!binHashTable->insert(phoneOwner));
                    cout << "Phone " << phoneOwner.phone << " is now in the bin file!" << endl;
                } else {

                    strcpy(phoneOwner.phone, phone.c_str());

                    cout << "Enter the address: ";
                    while (getline(cin, s) && s.empty());
                    cout << endl;
                    strcpy(phoneOwner.address, s.c_str());
                    s = "";

                    cout << "Enter the full name: ";
                    while (getline(cin, s) && s.empty());
                    cout << endl;
                    strcpy(phoneOwner.fullName, s.c_str());
                    s = "";

                    if (binHashTable->insert(phoneOwner)) {
                        cout << "Phone " << phone << " is now in the bin file!" << endl;
                    } else
                        cout << "Phone " << phone << " is already in the bin file!" << endl;
                }
                phone = "";
                break;

            case 7:

                cout << "How many elements you want to insert: ";
                cin >> enter;

                for (int j = 0; j < enter; j++) {
                    while (!binHashTable->insert(PhoneOwnerExtended::getRandomOwner(binHashTable->getBusy())));
                }
                cout << "Done!" << endl;

                break;

            case 8:

                cout << "Enter the phone number you want to delete (format: +7 (XXX) XXX-XX-XX): ";
                while (getline(cin, phone) && phone.empty());

                cout << endl;
                if (binHashTable->deleteElement(phone))
                    cout << "Phone " << phone << " was deleted!" << endl;
                else
                    cout << "Phone " << phone << " isn't in the table!" << endl;

                break;


            case 11:
                binTest(fstream1, fstream2, 1);
                break;

            case 12:
                binTest(fstream1, fstream2, 2);
                break;

            case 13:
                binTest(fstream1, fstream2, 3);
                break;

            case 14:
                binTest(fstream1, fstream2, 4);
                break;

            case 15:
                binTest(fstream1, fstream2, 5);
                break;

            case 16:
                binTestFind(fstream1, fstream2);
                break;

            default:
                cout << "Error. Try again!" << endl;
        }
        cout << endl;
    }
}

void Ex3_3::binTest(fstream &fstream1, fstream &fstream2, unsigned int testNum) {
    BinFileWithHashTable testBinTable("bin_test.dat", 0);
    testBinTable.insert(PhoneOwnerExtended("+7 (934) 934-03-93", 0));
    testBinTable.insert(PhoneOwnerExtended("+7 (244) 544-15-56", 1));
    testBinTable.insert(PhoneOwnerExtended("+7 (544) 254-26-19", 2));
    testBinTable.insert(PhoneOwnerExtended("+7 (944) 954-07-71", 3));
    testBinTable.insert(PhoneOwnerExtended("+7 (254) 564-19-34", 4));
    testBinTable.insert(PhoneOwnerExtended("+7 (554) 274-20-07", 5));
    testBinTable.insert(PhoneOwnerExtended("+7 (954) 874-01-69", 6));

    cout << "Data before test: " << endl;
    testBinTable.readAll();
    cout << endl;
    testBinTable.printTable();
    cout << endl;

    switch (testNum) {
        case 1:
            cout << "Insert phone +7 (611) 641-20-20" << endl << endl;
            testBinTable.insert(PhoneOwnerExtended("+7 (611) 641-20-20", 7), true);
            break;

        case 2:
            cout << "Insert with collision phone +7 (611) 641-20-24" << endl << endl;
            testBinTable.insert(PhoneOwnerExtended("+7 (611) 641-20-24", 7), true);
            break;

        case 3:
            cout << "Insert with update table phones +7 (611) 641-20-22, +7 (301) 021-15-81"
                 << endl;
            testBinTable.insert(PhoneOwnerExtended("+7 (611) 641-20-22", 7));
            testBinTable.insert(PhoneOwnerExtended("+7 (611) 641-20-24", 8));
            break;

        case 4:
            cout << "Delete phone +7 (254) 564-19-34" << endl << endl;
            testBinTable.deleteElement("+7 (254) 564-19-34");
            break;

        case 5:
            cout << "Find phone +7 (254) 564-19-34" << endl;
            cout << testBinTable.find("+7 (254) 564-19-34").to_string() << endl;
            break;
    }
    cout << endl;

    cout << "Data after test: " << endl;
    testBinTable.readAll();
    cout << endl;
    testBinTable.printTable();
}

void Ex3_3::binTestFind(fstream &fstream1, fstream &fstream2) {
    BinFileWithHashTable testBinTable("bin_test.dat", 1000000);

    testBinTable.exportToFile(fstream1);
    cout << "Test data is in files" << endl;

    string start = testBinTable.getElement(0).phone;
    string center = testBinTable.getElement(testBinTable.getBusy() / 2).phone;
    string end = testBinTable.getElement(testBinTable.getBusy() - 1).phone;

    cout << "Phones for search: " << start << ", " << center << ", " << end << endl << endl;

    time_t startTime, endTime;

    startTime = clock();
    cout << testBinTable.find(start).to_string() << endl;
    endTime = clock();
    cout << "Search time start: " << (double) (endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
    cout << endl;

    startTime = clock();
    cout << testBinTable.find(center).to_string() << endl;
    endTime = clock();
    cout << "Search time center: " << (double) (endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
    cout << endl;

    startTime = clock();
    cout << testBinTable.find(end).to_string() << endl;
    endTime = clock();
    cout << "Search time end: " << (double) (endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
    cout << endl;
}