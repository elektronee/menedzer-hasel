#include <iostream>
#include <cassert>
#include "klasy.h"

using namespace std;

void printTest(string name) {
    cout << "[OK] " << name << endl;
}

void test_user_register_login() {
    User user;
    user.registerUser("admin", "1234");

    assert(user.login("admin", "1234") == true);
    assert(user.login("1234", "admin") == false);
    assert(user.login("ala", "1234") == false);

    printTest("User: register + login");
}

void test_add_multiple_entries() {
    PasswordManager pm;

    pm.add("gmail", "u1", "p1");
    pm.add("facebook", "u2", "p2");
    pm.add("twitter", "u3", "p3");

    assert(pm.getSize() == 3);

    printTest("PM: add multiple entries");
}

void test_save_and_load() {
    PasswordManager pm;

    pm.add("gmail", "user1", "pass1");
    pm.add("fb", "user2", "pass2");

    pm.save("test.txt");

    PasswordManager pm2;
    pm2.load("test.txt");

    assert(pm2.getSize() == 2);

    printTest("PM: save + load");
}

void test_load_clears_previous_data() {
    PasswordManager pm;

    pm.add("temp", "x", "y");
    assert(pm.getSize() == 1);

    PasswordManager pm2;
    pm2.add("real", "user", "pass");
    pm2.save("test2.txt");

    pm.load("test2.txt");

    assert(pm.getSize() == 1);

    printTest("PM: load clears old data");
}


void test_overwrite_file() {
    PasswordManager pm;

    pm.add("a", "b", "c");
    pm.save("overwrite.txt");

    PasswordManager pm2;
    pm2.add("x", "y", "z");
    pm2.save("overwrite.txt");

    PasswordManager pm3;
    pm3.load("overwrite.txt");

    assert(pm3.getSize() == 1);

    printTest("PM: file overwrite");
}

int main() {
    cout << "testowanie\n\n";

    test_user_register_login();

    test_add_multiple_entries();

    test_save_and_load();
    test_load_clears_previous_data();
    test_overwrite_file();

    cout << "\nKOMPUER MÓWI OK\n";
    return 0;
}