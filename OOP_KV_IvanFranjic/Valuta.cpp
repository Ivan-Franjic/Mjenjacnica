#include "pch.h"
#include "Valuta.h"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;
Valuta::Valuta(string n, string i, string d, double iz, string dt)
{
	m_sNaziv = n;
	m_sIso = i;
	m_sDrzava = d;
	m_dIznos = iz;
	m_sDatum = dt;
}

Valuta::~Valuta()
{
}
