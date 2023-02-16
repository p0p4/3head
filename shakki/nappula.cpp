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

	Ruutu kohdeRuutu;
	Siirto siirto;

	for (int i = 0; i < maxAskelta; i++)
	{
		sarake += sarakeMuutos;
		rivi += riviMuutos;

		if (sarake < 0 || sarake > 7 || rivi < 0 || rivi > 7)
			break;

		kohdeRuutu.setSarake(sarake);
		kohdeRuutu.setRivi(rivi);

		siirto.setAlkuruutu(*ruutu);
		siirto.setLoppuruutu(kohdeRuutu);

		if (asema->_lauta[sarake][rivi] == NULL)
		{
			lista.push_back(siirto);
		}
		else
		{
			if (asema->_lauta[sarake][rivi]->getVari() != vari)
			{
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
	int varinSuunta = (vari == 0 ? 1 : -1);

	// korotus
	// if (rivi == (vari == 0 ? 6 : 1))
	// {
	// 	siirrotSuuntaan(lista, ruutu, asema, vari, 0, varinSuunta, 1);
	// 	lisaaSotilaanKorotukset(*siirto, lista, asema);
	// }

	// eteenpäin yksi
	if (asema->_lauta[sarake][rivi + varinSuunta] == NULL)
	{
		siirrotSuuntaan(lista, ruutu, asema, vari, 0, varinSuunta, 1);
		// eteenpäin kaksi
		if (rivi == (vari == 0 ? 1 : 6) && asema->_lauta[sarake][rivi + (2 * varinSuunta)] == NULL)
		{
			siirrotSuuntaan(lista, ruutu, asema, vari, 0, (2 * varinSuunta), 1);
		}
	}

	// viistoon
	if (asema->_lauta[sarake + 1][rivi + varinSuunta] != NULL)
	{
		siirrotSuuntaan(lista, ruutu, asema, vari, 1, varinSuunta, 1);
	}
	if (asema->_lauta[sarake - 1][rivi + varinSuunta] != NULL)
	{
		siirrotSuuntaan(lista, ruutu, asema, vari, -1, varinSuunta, 1);
	}

	// en passant
	if (asema->kaksoisaskelSarakkeella == -1)
		return;
	if (asema->kaksoisaskelSarakkeella == sarake + 1 && asema->_lauta[sarake + 1][rivi] != NULL 
	&& sarake + 1 < 8 && asema->_lauta[sarake + 1][rivi]->getKoodi() == (vari == 0 ? MS : VS))
	{
		siirrotSuuntaan(lista, ruutu, asema, vari, 1, varinSuunta, 1);
	}
	if (asema->kaksoisaskelSarakkeella == sarake - 1 && asema->_lauta[sarake - 1][rivi] != NULL 
	&& sarake - 1 >= 0 && asema->_lauta[sarake - 1][rivi]->getKoodi() == (vari == 0 ? MS : VS))
	{
		siirrotSuuntaan(lista, ruutu, asema, vari, -1, varinSuunta, 1);
	}
}

void Sotilas::lisaaSotilaanKorotukset(Siirto *siirto, std::list<Siirto> &lista, Asema *asema)
{
	int rivi = siirto->getLoppuruutu().getRivi();

	Siirto torniksi = *siirto;
	Siirto lahetiksi = *siirto;
	Siirto ratsuksi = *siirto;

	if (rivi == 7)
	{
		siirto->_miksikorotetaan = asema->vd;
		torniksi._miksikorotetaan = asema->vt;
		lahetiksi._miksikorotetaan = asema->vl;
		ratsuksi._miksikorotetaan = asema->vr;
	}
	else if (rivi == 0)
	{
		siirto->_miksikorotetaan = asema->md;
		torniksi._miksikorotetaan = asema->mt;
		lahetiksi._miksikorotetaan = asema->ml;
		ratsuksi._miksikorotetaan = asema->mr;
	}

	lista.push_back(*siirto);
	lista.push_back(torniksi);
	lista.push_back(lahetiksi);
	lista.push_back(ratsuksi);
}