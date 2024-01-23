//
// Created by gribk on 29.10.2023.
//

#include "Practice5.h"
#include "PhoneOwnerCut.h"
#include "BinaryTrees/BinarySearchTree.h"
#include "BinaryTrees/SplayTree.h"
#include "SearchClasses/HashTableSearch.h"
#include "FileWork/BinFileSearch.h"
#include <iostream>
#include <cstring>
#include <string>
#include <chrono>
#include <iomanip>
#include <random>

using namespace std;

void Practice5::start() {
    cout << "Practice 5" << endl;
    cout << endl;

    unsigned int enter;

    while (true) {
        cout << "Search structures:" << endl
             << "0 - exit;" << endl
             << "1 - binary search tree;" << endl
             << "2 - splay binary search tree;" << endl
             << "3 - hash table;" << endl
             << "9 - comparison." << endl;
        cout << "What to use?: ";
        cin >> enter;
        cout << endl;
        switch (enter) {
            case 0:
                cout << "Exit from practice 5." << endl;
                return;

            case 1:
                cout << "Work with binary search tree." << endl;
                cout << "Use bin file? (1 - yes, 0 - no): ";
                cin >> enter;

                if (enter == 1) {
                    withFile<BinarySearchTree>();
                } else {
                    withoutFile<BinarySearchTree>();
                }

                break;

            case 2:
                cout << "Work with splay binary tree." << endl;
                cout << "Use bin file? (1 - yes, 0 - no): ";
                cin >> enter;

                if (enter == 1) {
                    withFile<SplayTree>();
                } else {
                    withoutFile<SplayTree>();
                }
                break;

            case 3:
                cout << "Work with hash table." << endl;
                cout << "Use bin file? (1 - yes, 0 - no): ";
                cin >> enter;

                if (enter == 1) {
                    withFile<HashTableSearch>();
                } else {
                    withoutFile<HashTableSearch>();
                }
                break;

            case 9:
                comparison();
                break;

            default:
                cout << "Error. Try again!" << endl;
        }
        cout << endl;
    }
}

template<class T>
void Practice5::withoutFile() {
    cout << endl;
    int enter, i = 0;
    string phone;
    BinFileSearch::ISearchClass *searchObject = new T();

    cout << "Information about operations numbers:" << endl
         << "0 - exit from without file mode;" << endl
         << "1 - print operations info;" << endl
         << "2 - print struct;" << endl
         << "3 - find element;" << endl
         << "4 - insert element;" << endl
         << "5 - insert many random elements;" << endl
         << "6 - delete element." << endl
         << endl;

    while (true) {
        cout << "Enter operation number or 0 for exit: ";
        cin >> enter;

        switch (enter) {

            case 0:
                cout << "Exit from this mode." << endl;
                delete searchObject;
                return;

            case 1:
                cout << "Information about operations numbers:" << endl
                     << "0 - exit from without file mode;" << endl
                     << "1 - print operations info;" << endl
                     << "2 - print struct;" << endl
                     << "3 - find element;" << endl
                     << "4 - insert element;" << endl
                     << "5 - insert many random elements;" << endl
                     << "6 - delete element." << endl;
                break;

            case 2:
                searchObject->print();
                break;

            case 3:
                cout << "Enter the phone number you are looking for (format: +7 (XXX) XXX-XX-XX): ";
                while (getline(cin, phone) && phone.empty());

                enter = searchObject->find(phone);
                if (enter == -1)
                    cout << "The phone " << phone << " isn't in the struct!" << endl;
                else
                    cout << "The position of phone " << phone << " is " << enter << endl;

                phone = "";
                break;

            case 4:
                cout
                        << "Enter the phone number you want to insert (format: +7 (XXX) XXX-XX-XX) or 0 to insert random: ";
                while (getline(cin, phone) && phone.empty());

                if (phone == "0") phone = PhoneOwnerCut::getRandomPhoneNumber();

                if (searchObject->insert(phone, i)) {
                    cout << "Phone " << phone << " is now in the file!" << endl;
                    i++;
                } else
                    cout << "Phone " << phone << " is already in the struct!" << endl;

                break;

            case 5:

                cout << "How many elements you want to insert: ";
                cin >> enter;

                for (int j = 0; j < enter; j++) {
                    while (!searchObject->insert(PhoneOwnerCut::getRandomPhoneNumber(), i))
                        i++;
                    i++;
                }
                cout << "Done!" << endl;

                break;

            case 6:

                cout << "Enter the phone number you want to delete (format: +7 (XXX) XXX-XX-XX): ";
                while (getline(cin, phone) && phone.empty());

                if (searchObject->deleteElement(phone) != -1)
                    cout << "Phone " << phone << " was deleted!" << endl;
                else
                    cout << "Phone " << phone << " isn't in the struct!" << endl;

                break;

            default:
                cout << "Error. Try again!" << endl;
        }
        cout << endl;
    }
}

template<class T>
void Practice5::withFile() {
    int enter;
    cout << "Create new file? (1 - yes, 0 - no): ";
    cin >> enter;
    BinFileSearch *binFile;
    if (enter == 1) {
        cout << "Enter file size: ";
        cin >> enter;
        binFile = new BinFileSearch(new T(), "bin.dat", enter);
    } else {
        binFile = new BinFileSearch(new T(), "bin.dat");
    }
    cout << endl;

    string phone;
    string s;
    PhoneOwnerCut phoneOwner;

    cout << "Information about operations numbers:" << endl
         << "0 - exit from with file mode;" << endl
         << "1 - print operations info;" << endl
         << "2 - print struct;" << endl
         << "3 - print data from bin file;" << endl
         << "4 - find element;" << endl
         << "5 - insert element;" << endl
         << "6 - insert many random elements;" << endl
         << "7 - delete element." << endl
         << endl;

    while (true) {
        cout << "Enter operation number or 0 for exit: ";
        cin >> enter;

        switch (enter) {

            case 0:
                cout << "Exit from this mode." << endl;
                delete binFile;
                return;

            case 1:
                cout << "Information about operations numbers:" << endl
                     << "0 - exit from with file mode;" << endl
                     << "1 - print operations info;" << endl
                     << "2 - print struct;" << endl
                     << "3 - print data from bin file;" << endl
                     << "4 - find element;" << endl
                     << "5 - insert element;" << endl
                     << "6 - insert many random elements;" << endl
                     << "7 - delete element." << endl;
                break;

            case 2:
                binFile->printStruct();
                break;

            case 3:
                binFile->readAll();
                break;

            case 4:
                cout << "Enter the phone number you are looking for (format: +7 (XXX) XXX-XX-XX): ";
                while (getline(cin, phone) && phone.empty());

                phoneOwner = binFile->find(phone);
                if (phoneOwner.phone[0] == 0)
                    cout << "The phone " << phone << " isn't in the file!" << endl;
                else
                    cout << phoneOwner.to_string() << endl;

                phone = "";
                phoneOwner = PhoneOwnerCut();
                break;

            case 5:
                cout
                        << "Enter the phone number you want to insert (format: +7 (XXX) XXX-XX-XX) or 0 to insert random: ";
                while (getline(cin, phone) && phone.empty());

                if (phone == "0") {
                    do {
                        phoneOwner = PhoneOwnerCut::getRandomOwner();
                    } while (!binFile->insert(phoneOwner));
                    cout << "Phone " << phoneOwner.phone << " is now in the bin file!" << endl;
                } else {

                    strcpy(phoneOwner.phone, phone.c_str());

                    cout << "Enter the address: ";
                    while (getline(cin, s) && s.empty());

                    strcpy(phoneOwner.address, s.c_str());
                    s = "";


                    if (binFile->insert(phoneOwner)) {
                        cout << "Phone " << phone << " is now in the bin file!" << endl;
                    } else
                        cout << "Phone " << phone << " is already in the bin file!" << endl;
                }
                phone = "";
                break;

            case 6:

                cout << "How many elements you want to insert: ";
                cin >> enter;

                for (int j = 0; j < enter; j++) {
                    while (!binFile->insert(PhoneOwnerCut::getRandomOwner()));
                }
                cout << "Done!" << endl;
                break;

            case 7:

                cout << "Enter the phone number you want to delete (format: +7 (XXX) XXX-XX-XX): ";
                while (getline(cin, phone) && phone.empty());

                if (binFile->deleteElement(phone))
                    cout << "Phone " << phone << " was deleted!" << endl;
                else
                    cout << "Phone " << phone << " isn't in the file!" << endl;

                break;


            default:
                cout << "Error. Try again!" << endl;
        }
        cout << endl;
    }
}

void Practice5::comparison() {
    int enter, count;
    cout << "How many elements?: ";
    cin >> enter;
    cout << "How many elements you want to find?: ";
    cin >> count;
    vector<string> phoneToSearch;

    auto binFileWorkCut = new BinFileWorkCut("bin.dat");
    binFileWorkCut->fillBinFile(enter);

    if (count < 30)
        cout << "Phones for search:" << endl;
    for (int i = 0; i < count; i++) {
        phoneToSearch.push_back(binFileWorkCut->getElement((rand() * rand()) % enter).phone);
        if (count < 30)
            cout << phoneToSearch[i] << endl;
    }
    if (count < 30)
        cout << endl;
    cout << endl;
    delete binFileWorkCut;

    shuffle(phoneToSearch.begin(), phoneToSearch.end(), std::mt19937(std::random_device()()));

    cout << "Binary search tree:" << endl;
    test<BinarySearchTree>(phoneToSearch);
    cout << endl;
    cout << "Splay binary tree:" << endl;
    test<SplayTree>(phoneToSearch);
    cout << endl;
    cout << "Hash table:" << endl;
    test<HashTableSearch>(phoneToSearch);
    cout << endl;
}

template<class T>
void Practice5::test(const vector<string> &phones) {

    auto startTime = chrono::steady_clock::now();
    auto binFile = new BinFileSearch(new T(), "bin.dat");
    auto endTime = chrono::steady_clock::now();
    cout << "Init time: " << chrono::duration<double, std::chrono::seconds::period>(endTime - startTime).count()
         << " seconds" << endl;

    double sum = 0.0;
    PhoneOwnerCut phoneOwner;
    for (const string &phone: phones) {
        startTime = chrono::steady_clock::now();
        phoneOwner = binFile->find(phone);
        endTime = chrono::steady_clock::now();
        if (phones.size() < 30)
            cout << left << setw(125) << phoneOwner.to_string()
                 << " Search time: " << right << setw(8)
                 << chrono::duration<double, milli>(endTime - startTime).count()
                 << " milliseconds" << endl;
        sum += chrono::duration<double, milli>(endTime - startTime).count();
    }

    cout << "Average time: " << sum / (double) phones.size() << " milliseconds" << endl;

    delete binFile;
}
