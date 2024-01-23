//
// Created by gribk on 29.10.2023.
//

#include "BinFileSearch.h"

BinFileSearch::BinFileSearch(ISearchClass *searchObject, string fileName) : BinFileWorkCut(std::move(fileName)),
                                                                            searchObject(searchObject) {
    dataToSearchObject();
}

BinFileSearch::BinFileSearch(ISearchClass *searchObject, string fileName, int newFileSize) :
        BinFileWorkCut(std::move(fileName)), searchObject(searchObject) {
    fillBinFile(newFileSize);
    dataToSearchObject();
}


void BinFileSearch::dataToSearchObject() {

    file.open(fileName, ios::in | ios::binary);

    if (!file.is_open()) {
        cout << "Error while opening file!" << endl;
        exit(0);
    }

    PhoneOwnerCut phoneOwner{};
    file.read((char *) &phoneOwner, sizeof(PhoneOwnerCut));
    size = 0;
    while (!file.eof()) {
        if (!string(phoneOwner.phone).empty()) {
            searchObject->insert(phoneOwner.phone, (int) size);
            size++;
        }
        file.read((char *) &phoneOwner, sizeof(PhoneOwnerCut));
    }
    file.close();
}

PhoneOwnerCut BinFileSearch::find(const string &phone) {
    int position = searchObject->find(phone);
    return (position == -1) ? PhoneOwnerCut("", "") : getElement(position);
}

bool BinFileSearch::insert(PhoneOwnerCut phoneOwner) {

    if (searchObject->insert(phoneOwner.phone, (int) size)) {
        BinFileWorkCut::insert(phoneOwner, size);
        size++;
        return true;
    }

    return false;
}

bool BinFileSearch::deleteElement(const string &phoneNumber) {
    int position = searchObject->deleteElement(phoneNumber);

    if (position == -1)
        return false;

    BinFileWorkCut::deleteElement(position);
    size--;
    return true;
}

void BinFileSearch::printStruct() {
    searchObject->print();
}

unsigned int BinFileSearch::getSize() const {
    return size;
}

BinFileSearch::~BinFileSearch() {
    delete searchObject;
}

