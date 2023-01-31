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

void Nappula::siirtoSuuntaan(std::list<Siirto> &lista, Ruutu *ruutu, Asema *asema, int vari, int sarakeMuutos, int riviMuutos, int maxSuuntaAskelta)
{
	int sarake = ruutu->getSarake();
	int rivi = ruutu->getRivi();

	for (int i = 1; i <= maxSuuntaAskelta; i++)
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
				return;
			}
			break;
		}
	}
}

void Torni::annaSiirrot(std::list<Siirto> &lista, Ruutu *ruutu, Asema *asema, int vari)
{
	siirtoSuuntaan(lista, ruutu, asema, vari, 1, 0, 8);
	siirtoSuuntaan(lista, ruutu, asema, vari, -1, 0, 8);
	siirtoSuuntaan(lista, ruutu, asema, vari, 0, 1, 8);
	siirtoSuuntaan(lista, ruutu, asema, vari, 0, -1, 8);
}

void Ratsu::annaSiirrot(std::list<Siirto> &lista, Ruutu *ruutu, Asema *asema, int vari)
{
	siirtoSuuntaan(lista, ruutu, asema, vari, 1, 2, 1);
	siirtoSuuntaan(lista, ruutu, asema, vari, -1, 2, 1);
	siirtoSuuntaan(lista, ruutu, asema, vari, 1, -2, 1);
	siirtoSuuntaan(lista, ruutu, asema, vari, -1, -2, 1);
	siirtoSuuntaan(lista, ruutu, asema, vari, 2, 1, 1);
	siirtoSuuntaan(lista, ruutu, asema, vari, -2, 1, 1);
	siirtoSuuntaan(lista, ruutu, asema, vari, 2, -1, 1);
	siirtoSuuntaan(lista, ruutu, asema, vari, -2, -1, 1);
}

void Lahetti::annaSiirrot(std::list<Siirto> &lista, Ruutu *ruutu, Asema *asema, int vari)
{
	siirtoSuuntaan(lista, ruutu, asema, vari, 1, 1, 8);
	siirtoSuuntaan(lista, ruutu, asema, vari, -1, 1, 8);
	siirtoSuuntaan(lista, ruutu, asema, vari, 1, -1, 8);
	siirtoSuuntaan(lista, ruutu, asema, vari, -1, -1, 8);
}

void Daami::annaSiirrot(std::list<Siirto> &lista, Ruutu *ruutu, Asema *asema, int vari)
{
	Torni::annaSiirrot(lista, ruutu, asema, vari);
	Lahetti::annaSiirrot(lista, ruutu, asema, vari);
}

void Kuningas::annaSiirrot(std::list<Siirto> &lista, Ruutu *ruutu, Asema *asema, int vari)
{
	/*perusidea on ett� kaikki viereiset ruudut ovat sallittuja. kuten tornilla ja l�hetill�,
	oman nappulan p��lle ei voi menn� ja vastustajan nappulan voi sy�d�.

	Kaikki muu kuninkaaseen liittyv� tarkistus tehd��n eri paikassa*/

	siirtoSuuntaan(lista, ruutu, asema, vari, 1, 0, 1);
	siirtoSuuntaan(lista, ruutu, asema, vari, -1, 0, 1);
	siirtoSuuntaan(lista, ruutu, asema, vari, 0, 1, 1);
	siirtoSuuntaan(lista, ruutu, asema, vari, 0, -1, 1);

	siirtoSuuntaan(lista, ruutu, asema, vari, 1, 1, 1);
	siirtoSuuntaan(lista, ruutu, asema, vari, -1, 1, 1);
	siirtoSuuntaan(lista, ruutu, asema, vari, 1, -1, 1);
	siirtoSuuntaan(lista, ruutu, asema, vari, -1, -1, 1);
}

void Sotilas::annaSiirrot(std::list<Siirto> &lista, Ruutu *ruutu, Asema *asema, int vari)
{
	int sarake = ruutu->getSarake();
	int rivi = ruutu->getRivi();

	if (asema->_lauta[sarake][rivi + (vari == 0 ? 1 : -1)] == NULL)
	{
		siirtoSuuntaan(lista, ruutu, asema, vari, 0, vari == 0 ? 1 : -1, 1);
	}

	if (rivi == (vari == 0 ? 1 : 6) && asema->_lauta[sarake][rivi + (vari == 0 ? 2 : -2)] == NULL)
	{
		siirtoSuuntaan(lista, ruutu, asema, vari, 0, vari == 0 ? 2 : -2, 1);
	}

	if (asema->kaksoisaskelSarakkeella != -1)
	{
		if (asema->kaksoisaskelSarakkeella == sarake - 1)
		{
			siirtoSuuntaan(lista, ruutu, asema, vari, -1, vari == 0 ? 1 : -1, 1);
		}
		else if (asema->kaksoisaskelSarakkeella == sarake + 1)
		{
			siirtoSuuntaan(lista, ruutu, asema, vari, 1, vari == 0 ? 1 : -1, 1);
		}
	}

	if (asema->_lauta[sarake + 1][rivi + (vari == 0 ? 1 : -1)] == NULL &&
		asema->_lauta[sarake - 1][rivi + (vari == 0 ? 1 : -1)] == NULL)
	{
		return;
	}

	siirtoSuuntaan(lista, ruutu, asema, vari, 1, vari == 0 ? 1 : -1, 1);
	siirtoSuuntaan(lista, ruutu, asema, vari, -1, vari == 0 ? 1 : -1, 1);
}

void Sotilas::lisaaSotilaanKorotukset(Siirto *siirto, std::list<Siirto> &lista, Asema *asema)
{
}