#include <gtest/gtest.h>
#include "klasy.h"
#include <cstdio> // Dla funkcji remove()

// TEST 1: poprwaność logowania i haszowania
TEST(UserTest, RejestracjaILogowanie) {
    User u;
    u.registerUser("testowy_admin", "superTajne123");
    EXPECT_TRUE(u.login("testowy_admin", "superTajne123"));
    EXPECT_FALSE(u.login("testowy_admin", "zle_haslo"));
    EXPECT_FALSE(u.login("zly_login", "superTajne123"));
}

// TEST 2: poprawnie działanie listy haseł
TEST(PasswordManagerTest, DodawanieDoManagera) {
    PasswordManager pm;
    EXPECT_EQ(pm.getSize(), 0);
    pm.add("Google", "user_google", "hasloG");
    EXPECT_EQ(pm.getSize(), 1);
    pm.add("Facebook", "user_fb", "hasloF");
    EXPECT_EQ(pm.getSize(), 2);
}

// TEST 3: sprawdzanie integracji z plikiem
TEST(PasswordManagerTest, ZapisIOdczytZPliku) {
    std::string plikTestowy = "test_passwords.txt";
    PasswordManager pmZapis;
    pmZapis.add("Netflix", "Jan", "nHaslo");
    pmZapis.add("Steam", "Gracz", "sHaslo");
    pmZapis.save(plikTestowy);
    
    PasswordManager pmOdczyt;
    pmOdczyt.load(plikTestowy);
    EXPECT_EQ(pmOdczyt.getSize(), 2);
    
    std::remove(plikTestowy.c_str());
}

// TEST 4: sprawdzanie wypisywania haseł do konsoli (pusta lista)
TEST(PasswordManagerTest, WyswietlaniePustejListy) {
    PasswordManager pm;
    testing::internal::CaptureStdout();
    pm.show();
    std::string przechwyconyTekst = testing::internal::GetCapturedStdout();
    EXPECT_NE(przechwyconyTekst.find("Brak zapisanych hasel"), std::string::npos);
}

// TEST 5: sprawdzanie wypisywania haseł do konsoli (z elementami)
TEST(PasswordManagerTest, WyswietlanieZapisanychHasel) {
    PasswordManager pm;
    pm.add("GitHub", "programista", "mojeHaslo");
    pm.add("Spotify", "muzyk", "superMuza");
    testing::internal::CaptureStdout();
    pm.show();
    std::string przechwyconyTekst = testing::internal::GetCapturedStdout();
    EXPECT_NE(przechwyconyTekst.find("HASLA"), std::string::npos);
    EXPECT_NE(przechwyconyTekst.find("1. GitHub programista mojeHaslo"), std::string::npos);
    EXPECT_NE(przechwyconyTekst.find("2. Spotify muzyk superMuza"), std::string::npos);
}