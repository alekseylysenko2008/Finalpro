#pragma once
#include <iostream>
#include <cstdio>
#include <ctime>
using namespace std;

struct Contact {
    char name[30] = "none";
    char surname[30] = "none";
    char homePhone[20] = "-";
    char workPhone[20] = "-";
    char address[50] = "-";
    char email[40] = "-";
    int birthDay = 1;
    int birthMonth = 1;
    char group[20] = "other";
    bool blacklist = false;

    void input() {
        cout << "Name: "; cin.getline(name, 30);
        cout << "Surname: "; cin.getline(surname, 30);
        cout << "Home Phone: "; cin.getline(homePhone, 20);
        cout << "Work Phone: "; cin.getline(workPhone, 20);
        cout << "Address: "; cin.getline(address, 50);
        cout << "Email: "; cin.getline(email, 40);
        cout << "Birth Day (1-31): "; cin >> birthDay;
        cout << "Birth Month (1-12): "; cin >> birthMonth;
        cin.ignore();
        cout << "Group (family/friends/work): "; cin.getline(group, 20);
        cout << "In blacklist? (1 - yes, 0 - no): ";
        int bl; cin >> bl;
        blacklist = bl;
        cin.ignore();
    }

    void print() const {
        cout << surname << " " << name << ", " << group << endl;
        cout << "Home: " << homePhone << ", Work: " << workPhone << endl;
        cout << "Email: " << email << ", Address: " << address << endl;
        cout << "Birthday: " << birthDay << "." << birthMonth;
        if (blacklist) cout << " [BLACKLISTED]";
        cout << "\n------------------------\n";
    }

    void saveToFile(FILE* f) {
        fprintf(f, "%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n%s\n%d\n",
            name, surname, homePhone, workPhone, address, email,
            birthDay, birthMonth, group, blacklist ? 1 : 0);
    }

    void loadFromFile(FILE* f) {
        int bl;
        fscanf_s(f, "%s\n", name, (unsigned)_countof(name));
        fscanf_s(f, "%s\n", surname, (unsigned)_countof(surname));
        fscanf_s(f, "%s\n", homePhone, (unsigned)_countof(homePhone));
        fscanf_s(f, "%s\n", workPhone, (unsigned)_countof(workPhone));
        fscanf_s(f, "%s\n", address, (unsigned)_countof(address));
        fscanf_s(f, "%s\n", email, (unsigned)_countof(email));
        fscanf_s(f, "%d\n", &birthDay);
        fscanf_s(f, "%d\n", &birthMonth);
        fscanf_s(f, "%s\n", group, (unsigned)_countof(group));
        fscanf_s(f, "%d\n", &bl);
        blacklist = bl;
    }

    bool isBirthdaySoon() const {
        time_t now = time(0);
        tm ltm;
        localtime_s(&ltm, &now);
        int today = ltm.tm_mday;
        int thisMonth = ltm.tm_mon + 1;
        int daysAhead = 3;

        if (birthMonth == thisMonth) {
            return (birthDay >= today) && (birthDay <= today + daysAhead);
        }
        return false;
    }
};
