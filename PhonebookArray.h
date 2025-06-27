#pragma once
#include "Contact.h"

void addContact(Contact*& arr, int& size, const Contact& c) {
    Contact* newArr = new Contact[size + 1];
    for (int i = 0; i < size; ++i)
        newArr[i] = arr[i];
    newArr[size] = c;
    delete[] arr;
    arr = newArr;
    ++size;
}

void saveContacts(Contact* arr, int size, const char* filename) {
    FILE* f;
    fopen_s(&f, filename, "w");
    if (!f) return;
    fprintf(f, "%d\n", size);
    for (int i = 0; i < size; ++i)
        arr[i].saveToFile(f);
    fclose(f);
}

void loadContacts(Contact*& arr, int& size, const char* filename) {
    FILE* f;
    fopen_s(&f, filename, "r");
    if (!f) {
        size = 0;
        arr = nullptr;
        return;
    }
    fscanf_s(f, "%d\n", &size);
    arr = new Contact[size];
    for (int i = 0; i < size; ++i)
        arr[i].loadFromFile(f);
    fclose(f);
}

void listBlacklisted(Contact* arr, int size) {
    cout << "\n--- Blacklist ---\n";
    for (int i = 0; i < size; ++i)
        if (arr[i].blacklist)
            arr[i].print();
}

void listUpcomingBirthdays(Contact* arr, int size) {
    cout << "\n--- Upcoming Birthdays (3 days ahead) ---\n";
    for (int i = 0; i < size; ++i)
        if (arr[i].isBirthdaySoon())
            arr[i].print();
}
