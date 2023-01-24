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


void Torni::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int rivi = ruutu->getRivi();
	int sarake = ruutu->getSarake();
	int i = 1;

	while (rivi + i <= 7)
	{
		if (asema->_lauta[rivi + i][sarake] == NULL || asema->_lauta[rivi + i][sarake]->getVari() != vari)
		{
			Siirto siirto(Ruutu(rivi, sarake), Ruutu(rivi + i, sarake));
			lista.push_back(siirto);
		}
		else
		{
			break;
		}

		i++;
	}

	while (rivi - i >= 0)
	{
		if (asema->_lauta[rivi - i][sarake] == NULL || asema->_lauta[rivi - i][sarake]->getVari() != vari)
		{
			Siirto siirto(Ruutu(rivi, sarake), Ruutu(rivi - i, sarake));
			lista.push_back(siirto);
		}
		else
		{
			break;
		}

		i++;
	}

	while (sarake + i <= 7)
	{
		if (asema->_lauta[rivi][sarake + i] == NULL || asema->_lauta[rivi][sarake + i]->getVari() != vari)
		{
			Siirto siirto(Ruutu(rivi, sarake), Ruutu(rivi, sarake + i));
			lista.push_back(siirto);
		}
		else
		{
			break;
		}

		i++;
	}


	while (sarake - i >= 0)
	{
		if (asema->_lauta[rivi][sarake - i] == NULL || asema->_lauta[rivi][sarake - i]->getVari() != vari)
		{
			Siirto siirto(Ruutu(rivi, sarake), Ruutu(rivi, sarake - i));
			lista.push_back(siirto);
		}
		else
		{
			break;
		}

		i++;
	}
}


void Ratsu::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int rivi = ruutu->getRivi();
	int sarake = ruutu->getSarake();
	int i = 1;

	if (asema->_lauta[rivi + 2][sarake + 1] == NULL || asema->_lauta[rivi + 2][sarake + 1]->getVari() != vari)
	{
		if (rivi + 2 <= 7 && sarake + 1 <= 7)
		{
			Siirto siirto(Ruutu(rivi, sarake), Ruutu(rivi + 2, sarake + 1));
			lista.push_back(siirto);
		}
	}

	if (asema->_lauta[rivi + 2][sarake - 1] == NULL || asema->_lauta[rivi + 2][sarake + 1]->getVari() != vari)
	{
		if (rivi + 2 <= 7 && sarake - 1 >= 0)
		{
			Siirto siirto(Ruutu(rivi, sarake), Ruutu(rivi + 2, sarake + 1));
			lista.push_back(siirto);
		}
	}

	if (asema->_lauta[rivi - 2][sarake + 1] == NULL || asema->_lauta[rivi + 2][sarake + 1]->getVari() != vari)
	{
		if (rivi - 2 >= 0 && sarake + 1 <= 7)
		{
			Siirto siirto(Ruutu(rivi, sarake), Ruutu(rivi + 2, sarake + 1));
			lista.push_back(siirto);
		}
	}

	if (asema->_lauta[rivi - 2][sarake - 1] == NULL || asema->_lauta[rivi + 2][sarake + 1]->getVari() != vari)
	{
		if (rivi - 2 >= 0 && sarake - 1 >= 0)
		{
			Siirto siirto(Ruutu(rivi, sarake), Ruutu(rivi + 2, sarake + 1));
			lista.push_back(siirto);
		}
	}

	if (asema->_lauta[rivi + 1][sarake + 2] == NULL || asema->_lauta[rivi + 2][sarake + 1]->getVari() != vari)
	{
		if (rivi + 1 <= 7 && sarake + 2 <= 7)
		{
			Siirto siirto(Ruutu(rivi, sarake), Ruutu(rivi + 2, sarake + 1));
			lista.push_back(siirto);
		}
	}

	if (asema->_lauta[rivi + 1][sarake - 2] == NULL || asema->_lauta[rivi + 2][sarake + 1]->getVari() != vari)
	{
		if (rivi + 1 <= 7 && sarake - 2 >= 0)
		{
			Siirto siirto(Ruutu(rivi, sarake), Ruutu(rivi + 2, sarake + 1));
			lista.push_back(siirto);
		}
	}

	if (asema->_lauta[rivi - 1][sarake + 2] == NULL || asema->_lauta[rivi + 2][sarake + 1]->getVari() != vari)
	{
		if (rivi - 1 >= 0 && sarake + 2 <= 7)
		{
			Siirto siirto(Ruutu(rivi, sarake), Ruutu(rivi + 2, sarake + 1));
			lista.push_back(siirto);
		}
	}

	if (asema->_lauta[rivi - 1][sarake - 2] == NULL || asema->_lauta[rivi + 2][sarake + 1]->getVari() != vari)
	{
		if (rivi - 1 >= 0 && sarake - 2 >= 0)
		{
			Siirto siirto(Ruutu(rivi, sarake), Ruutu(rivi + 2, sarake + 1));
			lista.push_back(siirto);
		}
	}
}


void Lahetti::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int rivi = ruutu->getRivi();
	int sarake = ruutu->getSarake();
	int i = 1;


	while (rivi + i <= 7 && sarake + i <= 7)
	{
		if (asema->_lauta[rivi + i][sarake + i] == NULL || asema->_lauta[rivi + i][sarake]->getVari() != vari)
		{
			Siirto siirto(Ruutu(rivi, sarake), Ruutu(rivi + i, sarake + i));
			lista.push_back(siirto);
		}

		i++;
	}

	while (rivi - i >= 0 && sarake + i <= 7)
	{
		if (asema->_lauta[rivi - i][sarake + i] == NULL || asema->_lauta[rivi - i][sarake + i]->getVari() != vari)
		{
			Siirto siirto(Ruutu(rivi, sarake), Ruutu(rivi - i, sarake + i));
			lista.push_back(siirto);
		}
		else
		{
			break;
		}

		i++;
	}

	while (rivi + i <= 7 && sarake - i >= 0)
	{
		if (asema->_lauta[rivi + i][sarake - i] == NULL || asema->_lauta[rivi + i][sarake - i]->getVari() != vari)
		{
			Siirto siirto(Ruutu(rivi, sarake), Ruutu(rivi + i, sarake - i));
			lista.push_back(siirto);
		}
		else
		{
			break;
		}

		i++;
	}


	while (rivi - i >= 0 && sarake - i >= 0)
	{
		if (asema->_lauta[rivi - i][sarake - i] == NULL || asema->_lauta[rivi - i][sarake - i]->getVari() != vari)
		{
			Siirto siirto(Ruutu(rivi, sarake), Ruutu(rivi - i, sarake - i));
			lista.push_back(siirto);
		}
		else
		{
			break;
		}

		i++;
	}
}


void Daami::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{


}


void Kuningas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	/*perusidea on että kaikki viereiset ruudut ovat sallittuja. kuten tornilla ja lähetillä,
	oman nappulan päälle ei voi mennä ja vastustajan nappulan voi syödä.

	Kaikki muu kuninkaaseen liittyvä tarkistus tehdään eri paikassa*/

	int rivi = ruutu->getRivi();
	int sarake = ruutu->getSarake();

	if (asema->_lauta[rivi + 1][sarake] == NULL || asema->_lauta[rivi + 1][sarake]->getVari() != vari)
	{
		if (rivi + 1 <= 7)
		{
			Siirto siirto(Ruutu(rivi, sarake), Ruutu(rivi + 1, sarake));
			lista.push_back(siirto);
		}
	}

	if (asema->_lauta[rivi + 1][sarake + 1] == NULL || asema->_lauta[rivi + 1][sarake + 1]->getVari() != vari)
	{
		if (rivi + 1 <= 7 && sarake + 1 <= 7)
		{
			Siirto siirto(Ruutu(rivi, sarake), Ruutu(rivi + 1, sarake + 1));
			lista.push_back(siirto);
		}
	}

	if (asema->_lauta[rivi + 1][sarake - 1] == NULL || asema->_lauta[rivi + 1][sarake - 1]->getVari() != vari)
	{
		if (rivi + 1 <= 7 && sarake - 1 >= 0)
		{
			Siirto siirto(Ruutu(rivi, sarake), Ruutu(rivi + 1, sarake - 1));
			lista.push_back(siirto);
		}
	}

	if (asema->_lauta[rivi - 1][sarake] == NULL || asema->_lauta[rivi - 1][ruutu->getSarake()]->getVari() != vari)
	{
		if (rivi - 1 >= 0)
		{
			Siirto siirto(Ruutu(rivi, sarake), Ruutu(rivi - 1, sarake));
			lista.push_back(siirto);
		}
	}

	if (asema->_lauta[rivi - 1][sarake + 1] == NULL || asema->_lauta[rivi - 1][sarake + 1]->getVari() != vari)
	{
		if (rivi - 1 >= 0 && sarake + 1 <= 7)
		{
			Siirto siirto(Ruutu(rivi, sarake), Ruutu(rivi - 1, sarake + 1));
			lista.push_back(siirto);
		}
	}

	if (asema->_lauta[rivi - 1][sarake - 1] == NULL || asema->_lauta[rivi - 1][sarake - 1]->getVari() != vari)
	{
		if (rivi - 1 >= 0 && sarake - 1 >= 0)
		{
			Siirto siirto(Ruutu(rivi, sarake), Ruutu(rivi - 1, sarake - 1));
			lista.push_back(siirto);
		}
	}

	if (asema->_lauta[rivi][sarake + 1] == NULL || asema->_lauta[rivi][sarake + 1]->getVari() != vari)
	{
		if (sarake + 1 <= 7)
		{
			Siirto siirto(Ruutu(rivi, sarake), Ruutu(rivi, sarake + 1));
			lista.push_back(siirto);
		}
	}

	if (asema->_lauta[rivi][sarake - 1] == NULL || asema->_lauta[rivi][sarake - 1]->getVari() != vari)
	{
		if (sarake - 1 >= 0)
		{
			Siirto siirto(Ruutu(rivi, sarake), Ruutu(rivi, sarake - 1));
			lista.push_back(siirto);
		}
	}


}


void Sotilas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	if (vari == 0)
	{
		if (asema->_lauta[ruutu->getRivi() - 1][ruutu->getSarake()] == NULL)
		{
			Siirto siirto(Ruutu(ruutu->getRivi(), ruutu->getSarake()), Ruutu(ruutu->getRivi() - 1, ruutu->getSarake()));
			lista.push_back(siirto);

			if (asema->_lauta[ruutu->getRivi() - 2][ruutu->getSarake()] == NULL && ruutu->getRivi() == 7)
			{
				Siirto siirto(Ruutu(ruutu->getRivi(), ruutu->getSarake()), Ruutu(ruutu->getRivi() - 2, ruutu->getSarake()));
				lista.push_back(siirto);
			}
		}

		if (asema->_lauta[ruutu->getRivi() - 1][ruutu->getSarake() + 1]->getVari() == 1)
		{
			Siirto siirto(Ruutu(ruutu->getRivi(), ruutu->getSarake()), Ruutu(ruutu->getRivi() - 1, ruutu->getSarake() + 1));
			lista.push_back(siirto);
		}

		if (asema->_lauta[ruutu->getRivi() - 1][ruutu->getSarake() - 1]->getVari() == 1)
		{
			Siirto siirto(Ruutu(ruutu->getRivi(), ruutu->getSarake()), Ruutu(ruutu->getRivi() - 1, ruutu->getSarake() - 1));
			lista.push_back(siirto);
		}
	}


	if (vari == 1)
	{
		if (asema->_lauta[ruutu->getRivi() + 1][ruutu->getSarake()] == NULL)
		{
			Siirto siirto(Ruutu(ruutu->getRivi(), ruutu->getSarake()), Ruutu(ruutu->getRivi() + 1, ruutu->getSarake()));
			lista.push_back(siirto);

			if (asema->_lauta[ruutu->getRivi() + 2][ruutu->getSarake()] == NULL && ruutu->getRivi() == 2)
			{
				Siirto siirto(Ruutu(ruutu->getRivi(), ruutu->getSarake()), Ruutu(ruutu->getRivi() + 2, ruutu->getSarake()));
				lista.push_back(siirto);
			}
		}

		if (asema->_lauta[ruutu->getRivi() + 1][ruutu->getSarake() + 1]->getVari() == 0)
		{
			Siirto siirto(Ruutu(ruutu->getRivi(), ruutu->getSarake()), Ruutu(ruutu->getRivi() + 1, ruutu->getSarake() + 1));
			lista.push_back(siirto);
		}

		if (asema->_lauta[ruutu->getRivi() + 1][ruutu->getSarake() - 1]->getVari() == 0)
		{
			Siirto siirto(Ruutu(ruutu->getRivi(), ruutu->getSarake()), Ruutu(ruutu->getRivi() + 1, ruutu->getSarake() - 1));
			lista.push_back(siirto);
		}
	}
}




void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, std::list<Siirto>& lista, Asema* asema) {
	
}
