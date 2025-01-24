#include "Person.h"
#include <iostream>
#include <vector>

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
using std::cout;
using std::cin;
using std::endl;


//Setters
void Person::Set_imie(string imie)
{
	p_imie = imie;
}

void Person::Set_nazw(string nazw)
{
	p_nazw = nazw;
}

void Person::Set_id(int id)
{
	p_id = id;
}

void Person::Set_wiek(int wiek)
{
	p_wiek = wiek;
}

void Person::Set_adres(Adress adres)
{
	p_adres = adres;
}

//Getters
string Person::Get_imie() const
{
	return p_imie;
}

string Person::Get_nazw() const
{
	return p_nazw;
}

int Person::Get_id() const
{
	return p_id;
}

int Person::Get_wiek() const
{
	return p_wiek;
}

Adress Person::Get_adres() const
{
	return p_adres;
}

//Streamers

std::istream& operator >> (std::istream& pis, Person& i_pp)
{
	string imie;
	string nazwis;
	int index;
	int wiek;
	Adress adress;

	pis >> imie >> nazwis >> index >> wiek >> adress;
	
	i_pp.Set_imie(imie);
	i_pp.Set_nazw(nazwis);
	i_pp.Set_id(index);
	i_pp.Set_wiek(wiek);
	i_pp.Set_adres(adress);

	return pis;
}

std::ostream& operator << (std::ostream& pos, const Person& o_pp)
{
	pos << o_pp.Get_imie() << " " << o_pp.Get_nazw() << " " << o_pp.Get_id() << " " << o_pp.Get_wiek() << " " << o_pp.Get_adres();
	return pos;
}
