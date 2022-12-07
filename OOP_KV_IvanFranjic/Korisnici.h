#pragma once
#include <string>
using namespace std;
class Korisnici
{
public:
	Korisnici(string im, string prez, string kime, string loz);
	~Korisnici();
	string m_sIme;
	string m_sPrezime;
	string m_sKorisnicko_ime;
	string m_sLozinka;
	string DajKI();
	string DajPW();
	virtual void PrikaziIzbornik() = 0;
	
};

