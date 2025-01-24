#ifndef  Person_h
#define Person_h

#include <iostream>
#include <string>
#include <vector>
#include "Adress.h"


// UWAGI
/*
Do wykonania projektu, podczas procesu pisania programu:
inspirowano się lub zaadaptowano kod z książki “Introduction to Programming with C++ for Engineers”, autor: prof. dr hab. inż. Bogusław Cyganek,
wykorzystano bibliotekę nlohmann/json (plik json.hpp), autor: Niels Lohmann, udostepnioną pod adresem nlohmann/json: JSON for Modern C++ - GitHub, przy pracy z formatem JSON (na końcu dokumentu zamieszczono licencję),
inspirowano się lub zaadaptowano kod wygenerowany przez narzędzie ChatGPT 4,
inspirowano się lub zaadaptowano kod ze strony cppreference.com, zawierającą dokumentację i przykłady użycia dla języka C++.
inspirowano się lub zaadaptowano kod zaprezentowany na stronie Qt for Beginners.
*/

using std::string;
using std::vector;

// wprowadzanie - wyprowadzanie
using std::fstream;
using std::istream;
using std::ostream;

using std::ofstream;
using std::ifstream;
using std::ios;



class Person
{
public:
    //Setters

    //Metoda ustawia imi�
    void Set_imie(string imie);

    //Metoda ustawia nazwisko
    void Set_nazw(string nazw);

    //Metoda ustawia numer ID - niepowtarzalny parametr dla ka�dego rekordu
    void Set_id(int id);

    //Metoda ustawia wiek
    void Set_wiek(int wiek);

    //Metoda ustawia adres - parametry z klasy adres
    void Set_adres(Adress adres);

    //Getters
     
    //Metoda zwraca imi�
    string Get_imie() const;

    //Metoda zwraca nazwisko
    string Get_nazw() const;

    //Metoda zwraca numer ID
    int Get_id() const;

    //Metoda zwraca wiek
    int Get_wiek() const;

    //Metoda zwraca adres zamieszkania
    Adress Get_adres() const;

    friend ostream& operator << (ostream& pos, const Person& o_pp);
    friend istream& operator >> (istream& pis, Person& i_pp);

private:
    string p_imie;
    string p_nazw;
    int p_id;
    int p_wiek;
    Adress p_adres;
};

#endif // ! Person_h
