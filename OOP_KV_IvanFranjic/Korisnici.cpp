#include "pch.h"
#include "Korisnici.h"
#include <iostream>
#include <string>
#include "conio.h"
#include <thread>
#include <stdlib.h>

using namespace std;

Korisnici::Korisnici(string im, string prez, string kime, string loz)
{
	m_sIme = im;
	m_sPrezime = prez;
	m_sKorisnicko_ime = kime;
	m_sLozinka = loz;
}

string Korisnici::DajKI()
{
	return m_sKorisnicko_ime;
}

string Korisnici::DajPW()
{
	return m_sLozinka;
}

Korisnici::~Korisnici()
{
}
