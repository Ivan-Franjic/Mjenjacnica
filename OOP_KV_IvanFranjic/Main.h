#pragma once
#include "Korisnici.h"
#include <string>
using namespace std;
class Main : public Korisnici
{
public:
	Main(string im, string prez, string kime, string loz);
	~Main();
	void Login();
	void PrikaziKontrole();
	void PrikaziIzbornik();
	void PrikaziValute();
	void DodajValutu();
	void AzurirajValutu();
	void ObrisiValutu();
	void PronadiValutu();
	void DajMjenjacnica();
	string Date();
	void XMLObrisi(string siso);
};

