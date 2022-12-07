#pragma once
#include <string>

using namespace std;
class Valuta
{
public:
	Valuta(string n, string i, string d, double iz, string dt);
	~Valuta();
	string m_sNaziv;
	string m_sIso;
	string m_sDrzava;
	double m_dIznos;
	string m_sDatum;
	
};

