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

Person* DataBase::persona_do_edycji(int selected_id)
{
    for (auto& osoba : b_osoby) {
        if (osoba.Get_id() == selected_id) {
            return &osoba;  // zwraca wska�nik do osoby
        }
    }
    return nullptr;
}

pair<string, bool> DataBase::edytuj(int id, const string& nowe_imie, const string& nowe_nazwisko, int nowe_ID, int nowy_wiek, const string& nowa_miejscowosc, const string& nowa_ulica, int nowy_NrDomu, const string& nowy_kraj)
{
    auto iterator = find_if(b_osoby.begin(), b_osoby.end(), [&id](const Person& osoba) {
        return osoba.Get_id() == id;
    });

    if (iterator != b_osoby.end())
    {
        string wiadomosc_zwrotna;
        bool czy_zapis = true;

        iterator->Set_imie(nowe_imie);
        iterator->Set_nazw(nowe_nazwisko);
        iterator->Set_wiek(nowy_wiek);

        Adress nowy_adres;
        nowy_adres.Set_miejscowosc(nowa_miejscowosc);
        nowy_adres.Set_ulica(nowa_ulica);
        nowy_adres.Set_nrdomu(nowy_NrDomu);
        nowy_adres.Set_kraj(nowy_kraj);
        iterator->Set_adres(nowy_adres);

        if (nowe_ID != iterator->Get_id())
        {
            iterator->Set_id(nowe_ID);
            auto [zmieniono, nowe_ID] = id_sprawdz(*iterator);

            if (zmieniono)
            {
                wiadomosc_zwrotna = to_string(nowe_ID);
            }
        }

        czy_zapis = zapis("Baza_danych.json");

        return {wiadomosc_zwrotna, czy_zapis};
    }
}

// funkcja sprawdza unikalno�� ID i aktualizuje je jesli trzeba
pair<bool, int> DataBase::id_sprawdz(Person& w_person)
{
    int poszukiwane_id{ 1 };
    bool zmieniono{ false };

    for (const auto& id : b_osoby)
    {
        if ( (w_person.Get_id() == id.Get_id() && &w_person != &id) || w_person.Get_id() <= 0)   //jesli powtarza sie lub <= 0, zmieniamy i szukamy czy nie ma luki
        {
            zmieniono = true;

            while (true)
            {
                bool dziura = true;
                for (const auto& kolejny : b_osoby)
                {
                    if (kolejny.Get_id() == poszukiwane_id)  // Jesli jakas osoba ma id rowne szukanemu id to dajemy zna� poprzez "dziura" �e luki nie ma i szukamy dalej
                    {
                        dziura = false; // luka jest znaleziona wi�c operacje pomijane
                        poszukiwane_id++;
                        break;
                    }
                }
                if (dziura) // znaleziono brak wi�c ustawia id na �w brak
                {
                    w_person.Set_id(poszukiwane_id);
                    break;
                }
            }
        }
    }
    return {zmieniono, w_person.Get_id()};
}

tuple <bool, bool, int> DataBase::wprowadz(const string& im, const string& nazw, int id, int wiek, const string& miejsc, const string& ul, int nd, const string& kraj)
{
    Adress nadr;
    nadr.Set_miejscowosc(miejsc);
    nadr.Set_ulica(ul);
    nadr.Set_nrdomu(nd);
    nadr.Set_kraj(kraj);

    Person nosoba;
    nosoba.Set_imie(im);
    nosoba.Set_nazw(nazw);
    nosoba.Set_id(id);
    nosoba.Set_wiek(wiek);
    nosoba.Set_adres(nadr);

    bool bool_z_id = false;
    int int_z_id{0};
    std::tie(bool_z_id, int_z_id) = id_sprawdz(nosoba);

    b_osoby.push_back(nosoba);

    bool zapisujemy = true;
    zapisujemy = zapis("Baza_danych.json");

    return {zapisujemy, bool_z_id, int_z_id};
}

// Funkcja wykorzystywana przy wyszukiwaniu usuwanej osoby
BD DataBase::znajdz_usuwanego(int usuw_id)
{
    BD znaleziony_u;

    for (const auto& osoba_u : b_osoby)
    {
        if (usuw_id == osoba_u.Get_id())
        {
            znaleziony_u.push_back(osoba_u);
        }
    }

    return znaleziony_u; // Zwraca znalezion� osobe
}

void DataBase::usun(int kogo_u)
{
    auto znajdz = remove_if(b_osoby.begin(), b_osoby.end(),
        [&kogo_u](const Person& persona) {
            return persona.Get_id() == kogo_u; // por�wnuje numery id
        });

    if (znajdz != b_osoby.end())
    {
        b_osoby.erase(znajdz, b_osoby.end());
        zapis("Baza_danych.json");
    }

}

// ustawia litery w ciągu na małe
string DataBase::pomniejsz(const string& s)
{
    string zmniejsz = s;
    transform(zmniejsz.begin(), zmniejsz.end(), zmniejsz.begin(), ::tolower);
    return zmniejsz;
}

BD DataBase::wyszukaj_podfunkcja(char dana, const string& szukane)
{
    bool ok = true;
    int sz_wart{};

    string low_szukane = pomniejsz(szukane);

    try {
        sz_wart = stoi(szukane);
    } catch (const std::invalid_argument& e) {
        ok = false;  // je�li konwersja si� nie powiedzie, to ok ustawia na false
    }

    BD wyniki;

    switch (dana)
    {
    case 'I':
        for (const auto& szukany : b_osoby)
        {
            if (low_szukane == pomniejsz(szukany.Get_imie()))
            {
                wyniki.push_back(szukany);
            }
        }
        break;
    case 'N':
        for (const auto& szukany : b_osoby)
        {
            if (low_szukane == pomniejsz(szukany.Get_nazw()))
            {
                wyniki.push_back(szukany);
            }
        }
        break;

    case 'D':
        if (ok)
        {
            for (const auto& szukany : b_osoby)
            {
                if ( sz_wart == szukany.Get_id())
                {
                    wyniki.push_back(szukany);
                }
            }
        }
        break;
    case 'W':
        if (ok)
        {
            for (const auto& szukany : b_osoby)
            {
                if (sz_wart == szukany.Get_wiek())
                {
                    wyniki.push_back(szukany);
                }
            }
        }
        break;
    case 'J':
        for (const auto& szukany : b_osoby)
        {
            if (low_szukane == pomniejsz(szukany.Get_adres().Get_miejscowosc()))
            {
                wyniki.push_back(szukany);
            }
        }
        break;
    case 'U':
        for (const auto& szukany : b_osoby)
        {
            if (low_szukane == pomniejsz(szukany.Get_adres().Get_ulica()))
            {
                wyniki.push_back(szukany);
            }
        }
        break;
    case 'M':
        if (ok)
        {
            for (const auto& szukany : b_osoby)
            {
                if (sz_wart == szukany.Get_adres().Get_nrdomu())
                {
                    wyniki.push_back(szukany);
                }
            }
        }
        break;
    case 'K':
        for (const auto& szukany : b_osoby)
        {
            if (low_szukane == pomniejsz(szukany.Get_adres().Get_kraj()))
            {
                wyniki.push_back(szukany);
            }
        }
        break;
    default:
        break;
    }

    return wyniki;

}

// ZAPIS I ODCZYT

void DataBase::czy_plik_istnieje(const string& plik_nazwa)
{
    std::ifstream sprawdzany_plik(plik_nazwa);

    if (!sprawdzany_plik.is_open())
    {
        //cout << "Tworze nowy plik: ";
        std::ofstream nowy_plik(plik_nazwa);
        if (!nowy_plik.is_open())
        {
            //cout << "Blad: Nie mozna otworzyc pliku " << plik_nazwa << " do zapisu.\n";
            //perror("\nPowod");
            exit(1);
        }
        nowy_plik.close();
        return; // Jeśli nie ma co odczytywa�, to ko�czy funkcj�
    }
}

tuple<bool, int, string> DataBase::odczyt(const string& file_name)
{
    b_osoby.clear();

    czy_plik_istnieje(file_name);

    fstream plik(file_name, std::ios::in);

    bool blad = true;
    int kod_bledu = 0;

    if (!plik.is_open())
    {
        return {false, 1, ""};
    }

    try {
        json json_dane;

        // jeśli plik jest pusty
        if (plik.peek() == std::ifstream::traits_type::eof()) {
            kod_bledu = 2;
            blad = true;
            json_dane = json::array();  // inicjalizuje pustą tablicę json
        }
        else {
            plik >> json_dane;  // odczytuje dane z pliku json
        }

        plik.close();

        //Sprawdza czy są dane
        if (json_dane.empty()) {
            kod_bledu = 3;
            blad = false;
        }

        // przetwarzanie danych, dodawanie ich do bazy
        for (const auto& osoba_dana : json_dane) {
            Person person;
            person.Set_imie(osoba_dana["imie"]);
            person.Set_nazw(osoba_dana["nazwisko"]);
            person.Set_id(osoba_dana["id"]);
            person.Set_wiek(osoba_dana["wiek"]);

            Adress adres;
            adres.Set_miejscowosc(osoba_dana["adres"]["miejscowosc"]);
            adres.Set_ulica(osoba_dana["adres"]["ulica"]);
            adres.Set_nrdomu(osoba_dana["adres"]["numer_domu"]);
            adres.Set_kraj(osoba_dana["adres"]["kraj"]);

            person.Set_adres(adres);

            b_osoby.push_back(person);
        }

        return {blad, kod_bledu, ""};

    }
    catch (const json::exception& e) {          // obsluga bledow z odczytem lub niepoprawnym formatem json
        //exit(1); // zakończenie programu w przypadku błędu -- opcjonalne
        return {false, 4, e.what()};
    }
}

bool DataBase::zapis(const string& file_name)
{
    fstream plik(file_name, std::ios::out);

    if (!plik.is_open()) //jeśli nie można otworzyć pliku
    {
        return false;
    }

    json json_dane;

    // iteracja po rekordach i zapisywanie do obiektu json
    for (const auto& osoba : b_osoby)
    {
        json osoba_dana;
        osoba_dana["imie"] = osoba.Get_imie();
        osoba_dana["nazwisko"] = osoba.Get_nazw();
        osoba_dana["id"] = osoba.Get_id();
        osoba_dana["wiek"] = osoba.Get_wiek();

        json adres_dana;
        adres_dana["miejscowosc"] = osoba.Get_adres().Get_miejscowosc();
        adres_dana["ulica"] = osoba.Get_adres().Get_ulica();
        adres_dana["numer_domu"] = osoba.Get_adres().Get_nrdomu();
        adres_dana["kraj"] = osoba.Get_adres().Get_kraj();

        osoba_dana["adres"] = adres_dana;

        // dodaje dane osoby do obiektu json
        json_dane.push_back(osoba_dana);
    }

    // zapisuje dane do pliku
    plik << json_dane.dump(4);  // robi wcięcia dla lepszego formatowania

    plik.close();
    return true;
}
