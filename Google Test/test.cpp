#include "gtest/gtest.h"
#include "DataBase.h"

// UWAGI
/*
Do wykonania projektu, podczas procesu pisania programu:
inspirowano się lub zaadaptowano kod z książki “Introduction to Programming with C++ for Engineers”, autor: prof. dr hab. inż. Bogusław Cyganek,
wykorzystano bibliotekę nlohmann/json (plik json.hpp), autor: Niels Lohmann, udostepnioną pod adresem nlohmann/json: JSON for Modern C++ - GitHub, przy pracy z formatem JSON (na końcu dokumentu zamieszczono licencję),
inspirowano się lub zaadaptowano kod wygenerowany przez narzędzie ChatGPT 4,
inspirowano się lub zaadaptowano kod ze strony cppreference.com, zawierającą dokumentację i przykłady użycia dla języka C++.
inspirowano się lub zaadaptowano kod zaprezentowany na stronie Qt for Beginners.
*/

class DataBaseTest : public ::testing::Test {
protected:
    DataBase db;
    const std::string plik_test = "Baza_danych_test.json"; // plik testowy - przechowuje dane rekordów

    void SetUp() override {
        std::ofstream ofs(plik_test, std::ios::trunc); // nadpisanie pustym plikiem
        ofs.close();
        db.odczyt(plik_test);
    }

    void TearDown() override {
        std::remove(plik_test.c_str());  // czyszczenie pliku po te�cie
    }
};

// dodawanie osoby i wyszukiwanie po imieniu
TEST_F(DataBaseTest, Dodaj_rekord_i_wyszukaj_imie) {
    auto [zapis_danych, bool_id, int_id] = db.wprowadz("Jan", "Nowak", 1, 36, "Warszawa", "Srebrna", 21, "Polska");
    ASSERT_TRUE(zapis_danych);  // sprawdza tylko status zapisu
    auto osoby = db.wyszukaj_podfunkcja('I', "jAn"); //sprawdza dodatkowo czy funkcja wyszuka rekord niezale�nie od wielko�ci liter
    ASSERT_EQ(osoby.size(), 1);
    EXPECT_EQ(osoby[0].Get_imie(), "Jan");
    EXPECT_EQ(osoby[0].Get_nazw(), "Nowak");
    EXPECT_EQ(osoby[0].Get_id(), 1);
}

//wyszukiwanie wed�ug numeru ID
TEST_F(DataBaseTest, Wyszukaj_ID) {
    db.wprowadz("Monika", "Kowalska", 2, 25, "Krakow", "Szeroka", 45, "Polska");
    auto osoby = db.wyszukaj_podfunkcja('D', "2");
    ASSERT_EQ(osoby.size(), 1);
    EXPECT_EQ(osoby[0].Get_id(), 2);
    EXPECT_EQ(osoby[0].Get_imie(), "Monika");
    EXPECT_EQ(osoby[0].Get_nazw(), "Kowalska");
}

//wyszukiwanie wed�ug nazwiska
TEST_F(DataBaseTest, Wyszukaj_nazwisko) {
    db.wprowadz("Adam", "Wieczorek", 2, 25, "Krakow", "Szeroka", 45, "Polska");
    db.wprowadz("Adam", "Ranek", 987, 25, "Krakow", "Szeroka", 45, "Polska");
    db.wprowadz("Adam", "Poludnie", 876, 25, "Krakow", "Szeroka", 45, "Polska");
    auto osoby = db.wyszukaj_podfunkcja('N', "wieCZorEk");
    ASSERT_EQ(osoby.size(), 1);
    EXPECT_EQ(osoby[0].Get_id(), 2);
    EXPECT_EQ(osoby[0].Get_imie(), "Adam");
    EXPECT_EQ(osoby[0].Get_nazw(), "Wieczorek");
}

//wyszukiwanie wed�ug wieku
TEST_F(DataBaseTest, Wyszukaj_wiek) {
    db.wprowadz("Marek", "Lewandowski", 6, 29, "Kielce", "Piotrowska", 65, "Polska");
    db.wprowadz("John", "Smith", 7, 29, "New York", "Wall", 23, "United States of America");

    auto osoby = db.wyszukaj_podfunkcja('W', "29");
    ASSERT_EQ(osoby.size(), 2);
    EXPECT_EQ(osoby[0].Get_imie(), "Marek");
    EXPECT_EQ(osoby[1].Get_imie(), "John");
}

// Usuwanie rekordu
TEST_F(DataBaseTest, Usun_osobe) {
    db.wprowadz("Piotr", "Kowalski", 3, 44, "Gdansk", "Dluga", 13, "Polska");
    db.usun(3);
    auto osoby = db.wyszukaj_podfunkcja('D', "3");
    EXPECT_TRUE(osoby.empty()); // rekord powinien zostać usunięty
}

//Edycja osoby
TEST_F(DataBaseTest, Edycja_osoby) {
    db.wprowadz("Cezary", "Linda", 4, 51, "Wroclaw", "Szkolna", 6, "Polska");

    auto result = db.edytuj(4, "Boguslaw", "Pazura", 5, 37, "Siedlce", "Nadrzeczna", 20, "Polska");
    EXPECT_TRUE(result.second); // czy zapis si� powi�d�

    // weryfikowanie danych po edycji
    auto osoby = db.wyszukaj_podfunkcja('D', "5");
    ASSERT_EQ(osoby.size(), 1);
    EXPECT_EQ(osoby[0].Get_imie(), "Boguslaw");
    EXPECT_EQ(osoby[0].Get_nazw(), "Pazura");
    EXPECT_EQ(osoby[0].Get_id(), 5);
    EXPECT_EQ(osoby[0].Get_adres().Get_miejscowosc(), "Siedlce");
}

// zapis i odczyt
TEST_F(DataBaseTest, Zapis_i_odczyt) {

    db.wprowadz("Piotr", "Piotrowski", 3, 56, "Gdansk", "Listna", 32, "Polska");

    db.zapis(plik_test);

    DataBase n_db;

    n_db.odczyt(plik_test);

    auto osoby = n_db.wyszukaj_podfunkcja('D', "3");

    ASSERT_EQ(osoby.size(), 1); //powinna byc tylko jedna osoba o ID = 3
    EXPECT_EQ(osoby[0].Get_imie(), "Piotr");
    EXPECT_EQ(osoby[0].Get_nazw(), "Piotrowski");
    EXPECT_EQ(osoby[0].Get_id(), 3);
}
