#include <iostream>
#include "Contact.h"
#include "PhonebookArray.h"

using namespace std;

int main() {
    Contact* contacts = nullptr;
    int count = 0;
    loadContacts(contacts, count, "contacts.txt");

    int choice;
    do {
        cout << "\n==== Phonebook Menu ====\n";
        cout << "1. Show all contacts\n";
        cout << "2. Add contact\n";
        cout << "3. Show blacklist\n";
        cout << "4. Show birthdays in 3 days\n";
        cout << "0. Exit\n>> ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            for (int i = 0; i < count; ++i)
                contacts[i].print();
        }
        else if (choice == 2) {
            Contact c;
            c.input();
            addContact(contacts, count, c);
            cout << "Contact added.\n";
        }
        else if (choice == 3) {
            listBlacklisted(contacts, count);
        }
        else if (choice == 4) {
            listUpcomingBirthdays(contacts, count);
        }
    } while (choice != 0);

    saveContacts(contacts, count, "contacts.txt");
    delete[] contacts;
    cout << "Saved. Bye!\n";
    return 0;
}
