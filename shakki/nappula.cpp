#include <list>
#include <string>
#include "asema.h"
#include "nappula.h"
using namespace std;

Nappula::Nappula(wstring unicode, int vari, int koodi)
{
	setUnicode(unicode);
	setVari(vari);
	setKoodi(koodi);
}

void Nappula::siirrotSuuntaan(std::list<Siirto> &lista, Ruutu *ruutu, Asema *asema, int vari, int sarakeMuutos, int riviMuutos, int maxAskelta)
{
	int sarake = ruutu->getSarake();
	int rivi = ruutu->getRivi();

	for (int i = 0; i < maxAskelta; i++)
	{
		sarake += sarakeMuutos;
		rivi += riviMuutos;

		if (sarake < 0 || sarake > 7 || rivi < 0 || rivi > 7)
			break;

		if (asema->_lauta[sarake][rivi] == NULL)
		{
			Siirto siirto(Ruutu(ruutu->getSarake(), ruutu->getRivi()), Ruutu(sarake, rivi));
			lista.push_back(siirto);
		}
		else
		{
			if (asema->_lauta[sarake][rivi]->getVari() != vari)
			{
				Siirto siirto(Ruutu(ruutu->getSarake(), ruutu->getRivi()), Ruutu(sarake, rivi));
				lista.push_back(siirto);
			}
			break;
		}
	}
}

void Torni::annaSiirrot(std::list<Siirto> &lista, Ruutu *ruutu, Asema *asema, int vari)
{
	siirrotSuuntaan(lista, ruutu, asema, vari, 1, 0, 7);
	siirrotSuuntaan(lista, ruutu, asema, vari, -1, 0, 7);
	siirrotSuuntaan(lista, ruutu, asema, vari, 0, 1, 7);
	siirrotSuuntaan(lista, ruutu, asema, vari, 0, -1, 7);
}

void Ratsu::annaSiirrot(std::list<Siirto> &lista, Ruutu *ruutu, Asema *asema, int vari)
{
	siirrotSuuntaan(lista, ruutu, asema, vari, 1, 2, 1);
	siirrotSuuntaan(lista, ruutu, asema, vari, -1, 2, 1);
	siirrotSuuntaan(lista, ruutu, asema, vari, 1, -2, 1);
	siirrotSuuntaan(lista, ruutu, asema, vari, -1, -2, 1);
	siirrotSuuntaan(lista, ruutu, asema, vari, 2, 1, 1);
	siirrotSuuntaan(lista, ruutu, asema, vari, -2, 1, 1);
	siirrotSuuntaan(lista, ruutu, asema, vari, 2, -1, 1);
	siirrotSuuntaan(lista, ruutu, asema, vari, -2, -1, 1);
}

void Lahetti::annaSiirrot(std::list<Siirto> &lista, Ruutu *ruutu, Asema *asema, int vari)
{
	siirrotSuuntaan(lista, ruutu, asema, vari, 1, 1, 7);
	siirrotSuuntaan(lista, ruutu, asema, vari, -1, 1, 7);
	siirrotSuuntaan(lista, ruutu, asema, vari, 1, -1, 7);
	siirrotSuuntaan(lista, ruutu, asema, vari, -1, -1, 7);
}

void Daami::annaSiirrot(std::list<Siirto> &lista, Ruutu *ruutu, Asema *asema, int vari)
{
	Torni::annaSiirrot(lista, ruutu, asema, vari);
	Lahetti::annaSiirrot(lista, ruutu, asema, vari);
}

void Kuningas::annaSiirrot(std::list<Siirto> &lista, Ruutu *ruutu, Asema *asema, int vari)
{
	siirrotSuuntaan(lista, ruutu, asema, vari, 1, 0, 1);
	siirrotSuuntaan(lista, ruutu, asema, vari, -1, 0, 1);
	siirrotSuuntaan(lista, ruutu, asema, vari, 0, 1, 1);
	siirrotSuuntaan(lista, ruutu, asema, vari, 0, -1, 1);

	siirrotSuuntaan(lista, ruutu, asema, vari, 1, 1, 1);
	siirrotSuuntaan(lista, ruutu, asema, vari, -1, 1, 1);
	siirrotSuuntaan(lista, ruutu, asema, vari, 1, -1, 1);
	siirrotSuuntaan(lista, ruutu, asema, vari, -1, -1, 1);
}

void Sotilas::annaSiirrot(std::list<Siirto> &lista, Ruutu *ruutu, Asema *asema, int vari)
{
	int sarake = ruutu->getSarake();
	int rivi = ruutu->getRivi();

	// eteenpäin yksi
	if (asema->_lauta[sarake][rivi + (vari == 0 ? 1 : -1)] == NULL)
	{
		siirrotSuuntaan(lista, ruutu, asema, vari, 0, vari == 0 ? 1 : -1, 1);
		// eteenpäin kaksi
		if (rivi == (vari == 0 ? 1 : 6) && asema->_lauta[sarake][rivi + (vari == 0 ? 2 : -2)] == NULL)
		{
			siirrotSuuntaan(lista, ruutu, asema, vari, 0, vari == 0 ? 2 : -2, 1);
		}
	}

	// viistoon
	if (asema->_lauta[sarake + 1][rivi + (vari == 0 ? 1 : -1)] != NULL)
	{
		siirrotSuuntaan(lista, ruutu, asema, vari, 1, vari == 0 ? 1 : -1, 1);
	}
	if (asema->_lauta[sarake - 1][rivi + (vari == 0 ? 1 : -1)] != NULL)
	{
		siirrotSuuntaan(lista, ruutu, asema, vari, -1, vari == 0 ? 1 : -1, 1);
	}

	// en passant
	if (asema->kaksoisaskelSarakkeella != -1)
	{
		if (asema->kaksoisaskelSarakkeella == sarake - 1)
		{
			siirrotSuuntaan(lista, ruutu, asema, vari, -1, vari == 0 ? 1 : -1, 1);
		}
		else if (asema->kaksoisaskelSarakkeella == sarake + 1)
		{
			siirrotSuuntaan(lista, ruutu, asema, vari, 1, vari == 0 ? 1 : -1, 1);
		}
	}
}

void Sotilas::lisaaSotilaanKorotukset(Siirto *siirto, std::list<Siirto> &lista, Asema *asema)
{
}