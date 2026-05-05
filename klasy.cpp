#include "klasy.h"
#include <fstream>
#include <iostream>

// USER
void User::registerUser(string u, string p) {
    username = u;
    password = p;
}

bool User::login(string u, string p) {
    return (u == username && p == password);
}

// PASSWORD MANAGER
void PasswordManager::add(string service, string login, string password) {
    entries.push_back(service + ";" + login + ";" + password);
}

void PasswordManager::save(string filename) {
    ofstream file(filename);
    for (auto &e : entries) file << e << endl;
}

void PasswordManager::load(string filename) {
    entries.clear();
    ifstream file(filename);
    string line;
    while (getline(file, line)) entries.push_back(line);
}

int PasswordManager::getSize() {
    return entries.size();
}