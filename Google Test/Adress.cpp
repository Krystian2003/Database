#include <iostream>
#include "Adress.h"
#include <string>


// UWAGI
/*
Do wykonania projektu, podczas procesu pisania programu:
inspirowano siê lub zaadaptowano kod z ksi¹¿ki “Introduction to Programming with C++ for Engineers”, autor: prof. dr hab. in¿. Bogus³aw Cyganek,
wykorzystano bibliotekê nlohmann/json (plik json.hpp), autor: Niels Lohmann, udostepnion¹ pod adresem nlohmann/json: JSON for Modern C++ - GitHub, przy pracy z formatem JSON (na koñcu dokumentu zamieszczono licencjê),
inspirowano siê lub zaadaptowano kod wygenerowany przez narzêdzie ChatGPT 4,
inspirowano siê lub zaadaptowano kod ze strony cppreference.com, zawieraj¹c¹ dokumentacjê i przyk³ady u¿ycia dla jêzyka C++.
inspirowano siê lub zaadaptowano kod zaprezentowany na stronie Qt for Beginners.
*/


using std::string;
using std::cout;
using std::cin;
using std::endl;


using std::istream;
using std::ostream;


void Adress::Set_ulica(string ulica)
{
	a_ulica = ulica;
}

void Adress::Set_nrdomu(int nrdomu)
{
	a_nrdomu = nrdomu;
}

void Adress::Set_kraj(string kraj)
{
	a_kraj = kraj;
}

void Adress::Set_miejscowosc(string miejscowosc)
{
    a_miejscowosc = miejscowosc;
}

string Adress::Get_ulica() const
{
	return a_ulica;
}

int Adress::Get_nrdomu() const
{
	return a_nrdomu;
}

string Adress::Get_kraj() const
{
	return a_kraj;
}

string Adress::Get_miejscowosc() const
{
    return a_miejscowosc;
}

//Streamy
ostream& operator << (ostream& aos, const Adress& o_aa)
{
	
    aos << o_aa.Get_miejscowosc() << " " << o_aa.Get_ulica() << " " << o_aa.Get_nrdomu() << " " << o_aa.Get_kraj() << " ";
	
	return aos;
}

istream& operator >> (istream& ais, Adress& i_aa)
{
    string miejsc;
	string ulica;
	string kraj;
	int numdomu;

    ais >> miejsc;

	ais >> ulica;

	ais >> numdomu;

	ais >> kraj;

	//ais >> alley >> housenum >> country;
    i_aa.Set_miejscowosc(miejsc);
	i_aa.Set_ulica(ulica);
	i_aa.Set_nrdomu(numdomu);
	i_aa.Set_kraj(kraj);

	return ais;
}