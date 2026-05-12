#include "klasy.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
using namespace std;

//  HASZ
string User::hashPassword(string p) {
    stringstream ss;
    for (char c : p) {
        ss << hex << setw(2) << setfill('0') << (int)(c ^ 0x5A);
    }
    hash<string> bezpiecznyHasz;
    ss << hex << bezpiecznyHasz(p);
    return ss.str();
}

// USER

void User::registerUser(string u, string p) {
    username = u;
    passwordHash = hashPassword(p); 
}

bool User::login(string u, string p) {
    return (username == u && passwordHash == hashPassword(p));
}

// PASSWORDMANAGER 

void PasswordManager::add(string service, string login, string password) {

    string entry = service + " " + login + " " + password;
    entries.push_back(entry);
}

void PasswordManager::save(string filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (string entry : entries) {
            file << entry << "\n";
        }
        file.close();
    }
}

void PasswordManager::load(string filename) {
    ifstream file(filename);
    if (file.is_open()) {
        entries.clear();
        string line;
        while (getline(file, line)) {
            entries.push_back(line);
        }
        file.close();
    }
}

int PasswordManager::getSize() {
    return entries.size();
}

void PasswordManager::show() {
    if (entries.empty()) {
        cout << "Brak zapisanych haseł." << endl;
        return;
    }
    cout << "HASLA" << endl;
    for (int i = 0; i < entries.size(); i++) {
        cout << i + 1 << ". " << entries[i] << endl;
    }
}