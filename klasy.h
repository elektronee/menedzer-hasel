#pragma once
#include <vector>
#include <string>
using namespace std;

class User {
private:
    string username;
    string password;

public:
    void registerUser(string u, string p);
    bool login(string u, string p);
};

class PasswordManager {
private:
    vector<string> entries;

public:
    void add(string service, string login, string password);
    void save(string filename = "passwords.txt");
    void load(string filename = "passwords.txt");
    int getSize();
};