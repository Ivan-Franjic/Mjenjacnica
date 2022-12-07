#include "pch.h"
#include "Main.h"
#include "Korisnici.h"
#include "Valuta.h"
#include "tinyxml2.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include "conio.h"
#include <chrono>
#include <thread>
#include <stdlib.h>
#include "TextTable.h"
#include <ctime>

using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;
using namespace std;
using namespace tinyxml2;

Main::Main(string im, string prez, string kime, string loz) : Korisnici(im, prez, kime, loz)
{
}
//Funkcija za login
void Main::Login()
{
	system("CLS");
	cout << "DOBRODOSLI U MJENJACNICU" << endl;
	cout << " " << endl;
	vector<Korisnici*> vOsobe;
	vector<Korisnici*>::iterator ipos;

	XMLDocument oXmlDocument;
	oXmlDocument.LoadFile("config.xml");
	XMLElement *pRoot = oXmlDocument.FirstChildElement("data");
	XMLElement *pChild;
	XMLElement *pChildRoot;

	for (pChild = pRoot->FirstChildElement("Korisnici"); pChild != NULL; pChild = pChild->NextSiblingElement())
	{
		for (pChildRoot = pChild->FirstChildElement("korisnik"); pChildRoot != NULL; pChildRoot = pChildRoot->NextSiblingElement())
		{
			string sIme = pChildRoot->Attribute("ime");
			string sPrezime = pChildRoot->Attribute("prezime");
			string sKorisnicko_ime = pChildRoot->Attribute("korisnicko_ime");
			string sLozinka = pChildRoot->Attribute("lozinka");

			vOsobe.push_back(new Main(sIme, sPrezime, sKorisnicko_ime, sLozinka));
		}

	}
	bool prijava = false;
	string korisnicko_ime;
	cout << "Unesite korisnicko ime" << endl;
	cin >> korisnicko_ime;
	string pass = "";
	char ch;
	cout << "Unesite lozinku" << endl;
	ch = _getch();
	while (ch != 13 && ch != 8)
	{
		pass.push_back(ch);
		cout << '*';
		ch = _getch();

	}
	for (ipos = vOsobe.begin(); ipos != vOsobe.end(); ++ipos)
	{
		if (korisnicko_ime == ((*ipos)->DajKI()))
		{
			if (pass == ((*ipos)->DajPW()))
			{
				system("CLS");
				cout << "Uspjesna prijava" << endl;
				system("CLS");
				prijava = true;
				(*ipos)->PrikaziIzbornik();
			}
		}
	}
	if (prijava == false)
	{
		system("CLS");
		cout << "Prijava neuspjesna, pokusajte ponovno!" << endl;
		sleep_until(system_clock::now() + 1s);
		system("CLS");
		Login();
	}
}
//Funkcija za ispis valuta
void Main::PrikaziValute()
{
	cout << "PRIKAZ SVIH VALUTA" << endl;
	cout << " " << endl;
	vector<Valuta*> vPrikaziValute;
	XMLDocument oXmlDocument;
	oXmlDocument.LoadFile("rates.xml");
	XMLElement *pRoot = oXmlDocument.FirstChildElement("data");
	XMLElement *pChild;
	for (pChild = pRoot->FirstChildElement("valuta"); pChild != NULL; pChild =
		pChild->NextSiblingElement())
	{
			string sNaziv = pChild->Attribute("Naziv");
			string sISOcode = pChild->Attribute("ISO_code");
			string sDrzava = pChild->Attribute("Drzava");
			float fIznos = stof(pChild->Attribute("Iznos"));
			string sDatum = pChild->Attribute("Datum");
			vPrikaziValute.push_back(new Valuta(sNaziv, sISOcode, sDrzava, fIznos, sDatum));
	}
	int rb = 1;
	TextTable t('-', '|', '+');

	t.add("R.Br.");
	t.add("Naziv");
	t.add("Iso code");
	t.add("Drzava");
	t.add("Iznos");
	t.add("Datum");
	t.endOfRow();

	for (int i = 0; i < vPrikaziValute.size(); i++)
	{
		t.add(to_string(rb));
		t.add(vPrikaziValute[i]->m_sNaziv);
		t.add(vPrikaziValute[i]->m_sIso);
		t.add(vPrikaziValute[i]->m_sDrzava);
		t.add(to_string(vPrikaziValute[i]->m_dIznos));
		t.add(vPrikaziValute[i]->m_sDatum);
		t.endOfRow();
		rb++;
	}
	cout << t;
}
//Funkcija za dodavanje valuta
void Main::DodajValutu()
{
	cout << "DODAVANJE VALUTE" << endl;
	cout << " " << endl;
	string sNaziv;
	string sIso;
	string sDrzava;
	double dIznos;
	string sDatum = Date();
	cout << "Unesite naziv" << endl;
	cin >> sNaziv;	
	system("CLS");
	cout << "Unesite ISO code" << endl;
	cin >> sIso;
	system("CLS");
	cout << "Unesite drzavu" << endl;
	cin >> sDrzava;
	system("CLS");
	cout << "Unesite vrijednost tecaja" << endl;
	cin >> dIznos;
	system("CLS");
	XMLDocument xmlDoc;
	xmlDoc.LoadFile("rates.xml");
	XMLElement *pRoot = xmlDoc.FirstChildElement("data");
	XMLElement * pElement = xmlDoc.NewElement("valuta");
	pElement->SetAttribute("Naziv", sNaziv.c_str());
	pElement->SetAttribute("ISO_code", sIso.c_str());
	pElement->SetAttribute("Drzava", sDrzava.c_str());
	pElement->SetAttribute("Iznos", dIznos);
	pElement->SetAttribute("Datum", sDatum.c_str());
	pRoot->InsertEndChild(pElement);
	xmlDoc.SaveFile("rates.xml");
}
//Funkcija za azuriranje valuta
void Main::AzurirajValutu()
{
	cout << "AZURIRANJE VALUTE" << endl;
	cout << " " << endl;
	vector<Valuta*> vPrikaziValute;
	XMLDocument oXmlDocument;
	oXmlDocument.LoadFile("rates.xml");
	XMLElement *pRoot = oXmlDocument.FirstChildElement("data");
	XMLElement *pChild;
	for (pChild = pRoot->FirstChildElement("valuta"); pChild != NULL; pChild =
		pChild->NextSiblingElement())
	{
		string sNaziv = pChild->Attribute("Naziv");
		string sISOcode = pChild->Attribute("ISO_code");
		string sDrzava = pChild->Attribute("Drzava");
		float fIznos = stof(pChild->Attribute("Iznos"));
		string sDatum = pChild->Attribute("Datum");
		vPrikaziValute.push_back(new Valuta(sNaziv, sISOcode, sDrzava, fIznos, sDatum));
	}
	int rb = 1;
	TextTable t('-', '|', '+');

	t.add("R.Br.");
	t.add("Naziv");
	t.add("Iso code");
	t.add("Drzava");
	t.add("Iznos");
	t.add("Datum");
	t.endOfRow();

	for (int i = 0; i < vPrikaziValute.size(); i++)
	{
		t.add(to_string(rb));
		t.add(vPrikaziValute[i]->m_sNaziv);
		t.add(vPrikaziValute[i]->m_sIso);
		t.add(vPrikaziValute[i]->m_sDrzava);
		t.add(to_string(vPrikaziValute[i]->m_dIznos));
		t.add(vPrikaziValute[i]->m_sDatum);
		t.endOfRow();
		rb++;
	}
	cout << t;
	cout << " " << endl;
	cout << "Upisite redni broj valute koju zelite azurirati" << endl;
	int rbb;
	cin >> rbb;
	for (int i = 0; i < vPrikaziValute.size(); i++)
	{
		if (rbb - 1 == i)
		{
			string siso = vPrikaziValute[i]->m_sIso;
			vPrikaziValute.clear();
			XMLObrisi(siso);
		}
	}
	system("CLS");
	DodajValutu();
	cout << "Valuta uspjesno azurirana" << endl;
}
//Funkcija za brisanje valuta
void Main::ObrisiValutu()
{
	cout << "BRISANJE VALUTE" << endl;
	cout << " " << endl;
	vector<Valuta*> vPrikaziValute;
	XMLDocument oXmlDocument;
	oXmlDocument.LoadFile("rates.xml");
	XMLElement *pRoot = oXmlDocument.FirstChildElement("data");
	XMLElement *pChild;
	for (pChild = pRoot->FirstChildElement("valuta"); pChild != NULL; pChild =
		pChild->NextSiblingElement())
	{
		string sNaziv = pChild->Attribute("Naziv");
		string sISOcode = pChild->Attribute("ISO_code");
		string sDrzava = pChild->Attribute("Drzava");
		float fIznos = stof(pChild->Attribute("Iznos"));
		string sDatum = pChild->Attribute("Datum");
		vPrikaziValute.push_back(new Valuta(sNaziv, sISOcode, sDrzava, fIznos, sDatum));
	}
	int rb = 1;
	TextTable t('-', '|', '+');

	t.add("R.Br.");
	t.add("Naziv");
	t.add("Iso code");
	t.add("Drzava");
	t.add("Iznos");
	t.add("Datum");
	t.endOfRow();

	for (int i = 0; i < vPrikaziValute.size(); i++)
	{
		t.add(to_string(rb));
		t.add(vPrikaziValute[i]->m_sNaziv);
		t.add(vPrikaziValute[i]->m_sIso);
		t.add(vPrikaziValute[i]->m_sDrzava);
		t.add(to_string(vPrikaziValute[i]->m_dIznos));
		t.add(vPrikaziValute[i]->m_sDatum);
		t.endOfRow();
		rb++;
	}
	cout << t;
	cout << " " << endl;
	cout << "Upisite ISO code valute koju zelite obrisati" << endl;
	string siso;
	cin >> siso;
	vPrikaziValute.clear();
	XMLObrisi(siso);
	system("CLS");
	cout << "Valuta uspjesno obrisana" << endl;
}
//Pomocna funkcija za brisanje
void Main::XMLObrisi(string siso)
{
	XMLDocument oXmlDocument;
	oXmlDocument.LoadFile("rates.xml");
	XMLElement *pRoot = oXmlDocument.FirstChildElement("data");
	XMLElement *pChild;
	for (pChild = pRoot->FirstChildElement("valuta"); pChild != NULL; pChild =
		pChild->NextSiblingElement())
	{
		if (pChild->Attribute("ISO_code")==siso)
		{
			pRoot->DeleteChild(pChild);
			oXmlDocument.SaveFile("rates.xml");
			break;
		}
	}
}
//Funkcija za trazenje valuta
void Main::PronadiValutu()
{
	cout << "PRETRAZIVANJE VALUTA" << endl;
	cout << " " << endl;
	vector<Valuta*> vPrikaziValute;
	XMLDocument oXmlDocument;
	oXmlDocument.LoadFile("rates.xml");
	XMLElement *pRoot = oXmlDocument.FirstChildElement("data");
	XMLElement *pChild;
	for (pChild = pRoot->FirstChildElement("valuta"); pChild != NULL; pChild =
		pChild->NextSiblingElement())
	{
		string sNaziv = pChild->Attribute("Naziv");
		string sISOcode = pChild->Attribute("ISO_code");
		string sDrzava = pChild->Attribute("Drzava");
		float fIznos = stof(pChild->Attribute("Iznos"));
		string sDatum = pChild->Attribute("Datum");
		vPrikaziValute.push_back(new Valuta(sNaziv, sISOcode, sDrzava, fIznos, sDatum));
	}
		cout << "Upisite naziv drzave" << endl;
		string sdrzava;
		cin >> sdrzava;
		bool nasao = false;
		for (int i = 0; i < vPrikaziValute.size(); i++)
		{ 
			if (vPrikaziValute[i]->m_sDrzava == sdrzava)
			{
				system("CLS");
				cout << vPrikaziValute[i]->m_sNaziv << endl;
				cout << " " << endl;
				cout << "Iznos tecaja:" << " "<< vPrikaziValute[i]->m_dIznos << endl;
				nasao=true;
			}
		}
		if (nasao==false)
		{
			system("CLS");
			cout << "Drzava ne postoji" << endl;
			system("CLS");
			PronadiValutu();
		}
}
//Funkcija za prikaz mjenjacnice
void Main::DajMjenjacnica()
{
	cout << "MJENJACNICA" << endl;
	cout << " " << endl;
	vector<Valuta*> vPrikaziValute;
	XMLDocument oXmlDocument;
	oXmlDocument.LoadFile("rates.xml");
	XMLElement *pRoot = oXmlDocument.FirstChildElement("data");
	XMLElement *pChild;
	for (pChild = pRoot->FirstChildElement("valuta"); pChild != NULL; pChild =
		pChild->NextSiblingElement())
	{
		string sNaziv = pChild->Attribute("Naziv");
		string sISOcode = pChild->Attribute("ISO_code");
		string sDrzava = pChild->Attribute("Drzava");
		float fIznos = stof(pChild->Attribute("Iznos"));
		string sDatum = pChild->Attribute("Datum");
		vPrikaziValute.push_back(new Valuta(sNaziv, sISOcode, sDrzava, fIznos, sDatum));
	}
	int rb = 1;
	TextTable t('-', '|', '+');

	t.add("R.Br.");
	t.add("Naziv");
	t.add("Iso code");
	t.add("Drzava");
	t.add("Iznos");
	t.add("Datum");
	t.endOfRow();

	for (int i = 0; i < vPrikaziValute.size(); i++)
	{
		t.add(to_string(rb));
		t.add(vPrikaziValute[i]->m_sNaziv);
		t.add(vPrikaziValute[i]->m_sIso);
		t.add(vPrikaziValute[i]->m_sDrzava);
		t.add(to_string(vPrikaziValute[i]->m_dIznos));
		t.add(vPrikaziValute[i]->m_sDatum);
		t.endOfRow();
		rb++;
	}
	cout << t;
	cout << " " << endl;
	bool nasao = false;
	bool nasao2 = false;
	cout << "Odaberite ISO code izvorisne valute" << endl;
	string sIsoCode1;
	cin >> sIsoCode1;
	cout << "Odaberite ISO code odredisne valute" << endl;
	string sIsoCode2;
	cin >> sIsoCode2;
	cout << "Unesite iznos koji zelite promijeniti" << endl;
	double dIznos;
	cin >> dIznos;
	double dPrvaVrijednost = 0;
	double dRezultat = 0;
	string sHr = "HRK";
	for (int i = 0; i < vPrikaziValute.size(); i++)
	{
		if (vPrikaziValute[i]->m_sIso == sIsoCode1)
		{
			dPrvaVrijednost = dIznos * vPrikaziValute[i]->m_dIznos;
			nasao = true;
		}
	}
	for (int i = 0; i < vPrikaziValute.size(); i++)
	{
		if (sHr == sIsoCode1)
		{
			dPrvaVrijednost = dIznos;
			nasao = true;
		}
	}
	for (int i = 0; i < vPrikaziValute.size(); i++)
	{
		if (vPrikaziValute[i]->m_sIso == sIsoCode2)
		{
			dRezultat = dPrvaVrijednost / vPrikaziValute[i]->m_dIznos;
			nasao2 = true;
		}
	}
	for (int i = 0; i < vPrikaziValute.size(); i++)
	{
		if (sHr == sIsoCode2)
		{
			dRezultat = dPrvaVrijednost;
			nasao2 = true;
		}
	}
	if (nasao == false)
	{
		system("CLS");
		cout <<"Uneseni ISO code ne postoji, pokusajte ponovno"<< endl;
		sleep_until(system_clock::now() + 2s);
		system("CLS");
		DajMjenjacnica();
	}
	if (nasao2 == false)
	{
		system("CLS");
		cout << "Uneseni ISO code ne postoji, pokusajte ponovno" << endl;
		sleep_until(system_clock::now() + 2s);
		system("CLS");
		DajMjenjacnica();
	}
	system("CLS");
	cout << dIznos << " " << sIsoCode1 << " " << "je" << " " << dRezultat << " " << sIsoCode2 << endl;
}
//Izbornik s kontrolama
void Main::PrikaziKontrole()
{
	cout << "Pritisnite [Q] za povratak u glavni izbornik" << endl;
	cout << "Pritisnite [X] za izlaz iz programa" << endl;
	cout << "Vas odabir: " << endl;
	int odabir2 = _getch();
	/*
	 88 - X
	 81 - Q
	 113 - q
	 120 - x
	*/
	while (odabir2 != 81 && odabir2 != 88 && odabir2 != 113 && odabir2 != 120)
	{
		cout << "Krivi odabir, pokusajte ponovno" << endl;
		cout << " " << endl;
		cout << "Vas odabir: " << endl;
		odabir2 = _getch();
	}
	switch (odabir2)
	{
	case 81:
		system("CLS");
		PrikaziIzbornik();
		break;

	case 113:
		system("CLS");
		PrikaziIzbornik();
		break;

	case 88:
		system("CLS");
		exit(0);
		break;

	case 120:
		system("CLS");
		exit(0);
		break;
	}
}
//Glavni izbornik
void Main::PrikaziIzbornik()
{
	cout << "GLAVNI IZBORNIK" << endl;
	cout << " " << endl;
	cout << "1) Pregledaj sve valute" << endl;
	cout << "2) Dodaj valutu" << endl;
	cout << "3) Azuriraj valutu" << endl;
	cout << "4) Obrisi valutu" << endl;
	cout << "5) Pronadi valutu" << endl;
	cout << "6) Mjenjacnica" << endl;
	cout << "7) Izlaz" << endl;
	int odabir = _getch();

	while (odabir != 49 && odabir != 50 && odabir != 51 && odabir != 52 && odabir != 53 && odabir != 54 && odabir != 55)
	{
		cout << "Krivi odabir, pokusajte ponovno" << endl;
		cout << " " << endl;
		cout << "Vas odabir: " << endl;
		odabir = _getch();
	}

	switch (odabir)
	{
	case 49: //1
		system("CLS");
		PrikaziValute();
		cout << " " << endl;
		PrikaziKontrole();
		break;

	case 50: //2
		system("CLS");
		DodajValutu();
		cout << "Uspjesno dodana nova valuta" << endl;
		cout << " " << endl;
		PrikaziKontrole();
		break;

	case 51: //3
		system("CLS");
		AzurirajValutu();
		cout << " " << endl;
		PrikaziKontrole();
		break;

	case 52: //4
		system("CLS");
		ObrisiValutu();
		cout << " " << endl;
		PrikaziKontrole();
		break;

	case 53: //5
		system("CLS");
		PronadiValutu();
		cout << " " << endl;
		PrikaziKontrole();
		break;

	case 54: //6
		system("CLS");
		DajMjenjacnica();
		cout << " " << endl;
		PrikaziKontrole();
		break;

	case 55: //7
		system("CLS");
		cout << "Odjava..." << endl;
		sleep_until(system_clock::now() + 2s);
		system("CLS");
		break;

	}
}
//Funkcija za dohvacanje datuma
string Main::Date()
{
	time_t t = time(0);
	tm* now = localtime(&t);
	return to_string(now->tm_mday) + "/" + to_string((now->tm_mon + 1)) + "/" + to_string((now->tm_year + 1900));
}

Main::~Main()
{
}
