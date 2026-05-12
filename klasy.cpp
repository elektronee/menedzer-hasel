#include "klasy.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
using namespace std;
//  HASZ
string User::hashPassword(string u, string p) {
    string salt = "123lol654";
    string saltedPassword = u + sol + p;

    stringstream ss;

    // klucz zależy teraz od pozycji znaku
    for (int i = 0; i < saltedPassword.length(); i++) {
        // 0x5A + pozycja litery (modulo 256, żeby nie wyjść poza zakres char)
        char zmiennyKlucz = 0x5A ^ (i % 256); 
        ss << hex << setw(2) << setfill('0') << (int)(saltedPassword[i] ^ zmiennyKlucz);
    }
    hash<string> bezpiecznyHasz;
    size_t wynikHaszowania = bezpiecznyHasz(saltedPassword);
    ffor(int i = 0; i < 10000; i++) {
        wynikHaszowania = bezpiecznyHasz(to_string(wynikHaszowania));
    }
    ss << hex << bezpiecznyHasz(p);
    return ss.str();
}

// USER

void User::registerUser(string u, string p) {
    username = u;
    passwordHash = hashPassword(u, p); 
}

bool User::login(string u, string p) {
    return (username == u && passwordHash == hashPassword(u, p));
}

// PASSWORDMANAGER 

void PasswordManager::add(string service, string login, string password) {

    string entry = service + " " + login + " " + password;
    entries.push_back(entry);
}

void PasswordManager::save(string filename) {
    ofstream file(filename);
    if (file.is_open()) {
        char klucz = 0x5A; 
        for (string entry : entries) {
            string zaszyfrowanyWpis = entry;
            for (int i = 0; i < zaszyfrowanyWpis.length(); i++) {
                zaszyfrowanyWpis[i] = zaszyfrowanyWpis[i] ^ klucz;
            }
            file << zaszyfrowanyWpis << "\n";
        }
        file.close();
    }
}

void PasswordManager::load(string filename) {
    ifstream file(filename);
    if (file.is_open()) {
        entries.clear();
        string line;
        char klucz = 0x5A; 
        
        while (getline(file, line)) {
            string odszyfrowanyWpis = line;
                        for (int i = 0; i < odszyfrowanyWpis.length(); i++) {
                odszyfrowanyWpis[i] = odszyfrowanyWpis[i] ^ klucz;
            }
            
            entries.push_back(odszyfrowanyWpis);
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