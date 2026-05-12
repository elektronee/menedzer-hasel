#include <iostream>
#include <cstdlib>
#include "klasy.h"

using namespace std;

int main() {
    User uzytkownik;
    PasswordManager manager;

    uzytkownik.registerUser("admin", "tajne123");
    
    string login, haslo;
    cout << "Podaj login: "; cin >> login;
    cout << "Podaj haslo: "; cin >> haslo;
    
    if (uzytkownik.login(login, haslo)) {
        cout << "Zalogowano pomyślnie!" << endl;
        manager.load();
        
        int wybor;
        do {
            cout << "\n1. Dodaj haslo\n2. Pokaz hasla\n3. Zapisz i wyjdz\nWybor: ";
            cin >> wybor;
            
            if (wybor == 1) {
                string s, l, h;
                cout << "Serwis: "; cin >> s;
                cout << "Login: "; cin >> l;
                cout << "Haslo "; cin >> h;                
                manager.add(s, l, h);
            } 
            else if (wybor == 2) {
                manager.show();
            }
            else if (wybor == 3) {
                manager.save();
                cout << "Zapisano " << endl;
            }
        } while (wybor != 3);
        
    } else {
        cout << "Bledne dane logowania!" << endl;
    }
    
    return 0;
}