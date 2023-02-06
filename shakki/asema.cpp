#include <iostream>
#include "asema.h"
#include "minmaxpaluu.h"
#include "nappula.h"
#include "ruutu.h"
using namespace std;

Nappula *Asema::vk = new Kuningas(L"\u2654", 0, VK);
Nappula *Asema::vd = new Daami(L"\u2655", 0, VD);
Nappula *Asema::vt = new Torni(L"\u2656", 0, VT);
Nappula *Asema::vl = new Lahetti(L"\u2657", 0, VL);
Nappula *Asema::vr = new Ratsu(L"\u2658", 0, VR);
Nappula *Asema::vs = new Sotilas(L"\u2659", 0, VS);

Nappula *Asema::mk = new Kuningas(L"\u265A", 1, MK);
Nappula *Asema::md = new Daami(L"\u265B", 1, MD);
Nappula *Asema::mt = new Torni(L"\u265C", 1, MT);
Nappula *Asema::ml = new Lahetti(L"\u265D", 1, ML);
Nappula *Asema::mr = new Ratsu(L"\u265E", 1, MR);
Nappula *Asema::ms = new Sotilas(L"\u265F", 1, MS);

Asema::Asema()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			_lauta[i][j] = NULL;
		}
	}

	_lauta[0][7] = mt;
	_lauta[1][7] = mr;
	_lauta[2][7] = ml;
	_lauta[3][7] = md;
	_lauta[4][7] = mk;
	_lauta[5][7] = ml;
	_lauta[6][7] = mr;
	_lauta[7][7] = mt;

	for (int i = 0; i < 8; i++)
	{
		_lauta[i][6] = ms;
	}

	for (int i = 0; i < 8; i++)
	{
		_lauta[i][1] = vs;
	}

	_lauta[0][0] = vt;
	_lauta[1][0] = vr;
	_lauta[2][0] = vl;
	_lauta[3][0] = vd;
	_lauta[4][0] = vk;
	_lauta[5][0] = vl;
	_lauta[6][0] = vr;
	_lauta[7][0] = vt;

	setSiirtovuoro(0);

	_onkoValkeaKuningasLiikkunut = false;
	_onkoMustaKuningasLiikkunut = false;
	_onkoValkeaDTliikkunut = false;
	_onkoValkeaKTliikkunut = false;
	_onkoMustaDTliikkunut = false;
	_onkoMustaKTliikkunut = false;
}

void Asema::paivitaAsema(Siirto *siirto)
{
	int aS, aR;
	int lS, lR;

	aS = siirto->getAlkuruutu().getSarake();
	aR = siirto->getAlkuruutu().getRivi();

	lS = siirto->getLoppuruutu().getSarake();
	lR = siirto->getLoppuruutu().getRivi();

	// Kaksoisaskel-lippu on oletusarvoisesti pois p��lt�.
	// Asetetaan my�hemmin, jos tarvii.

	// Tarkastetaan on siirto lyhyt linna
	if (siirto->onkoLyhytLinna())
	{
		int rivi = 7 * getSiirtovuoro();
		_lauta[6][rivi] = _lauta[4][rivi];
		_lauta[5][rivi] = _lauta[7][rivi];
		_lauta[4][rivi] = NULL;
		_lauta[7][rivi] = NULL;
	}
	// onko pitk� linna
	else if (siirto->onkoPitkalinna())
	{
		int rivi = 7 * getSiirtovuoro();
		_lauta[2][rivi] = _lauta[4][rivi];
		_lauta[3][rivi] = _lauta[0][rivi];
		_lauta[4][rivi] = NULL;
		_lauta[0][rivi] = NULL;
	}
	// Kaikki muut siirrot
	else
	{
		// Ottaa siirron alkuruudussa olleen nappulan talteen

		// Ohestaly�nti on tyhj��n ruutuun. Vieress� oleva (sotilas) poistetaan.
		if (kaksoisaskelSarakkeella != -1)
		{
			if (_lauta[aS][aR] == vs && lS == kaksoisaskelSarakkeella)
			{
				_lauta[lS][lR - 1] = NULL;
			}
			else if (_lauta[aS][aR] == ms && lS == kaksoisaskelSarakkeella)
			{
				_lauta[lS][lR + 1] = NULL;
			}
		}

		// Tarkistetaan oliko sotilaan kaksoisaskel
		// (asetetaan kaksoisaskel-lippu)
		if (_lauta[aS][aR] == vs && aR == 1 && lR == 3)
		{
			kaksoisaskelSarakkeella = lS;
		}
		else if (_lauta[aS][aR] == ms && aR == 6 && lR == 4)
		{
			kaksoisaskelSarakkeella = lS;
		}
		else
		{
			kaksoisaskelSarakkeella = -1;
		}

		// Laittaa talteen otetun nappulan uuteen ruutuun

		//// Katsotaan jos nappula on sotilas ja rivi on p��tyrivi niin ei vaihdeta nappulaa
		////eli alkuruutuun laitetaan null ja loppuruudussa on jo kliittym�n laittama nappula MIIKKA, ei taida minmaxin kanssa hehkua?

		////muissa tapauksissa alkuruutuun null ja loppuruutuun sama alkuruudusta l�htenyt nappula
		if (!(_lauta[aS][aR] == vs && lR == 7) && !(_lauta[aS][aR] == ms && lR == 0))
		{
			_lauta[lS][lR] = _lauta[aS][aR];
		}
		_lauta[aS][aR] = NULL;
	}

	// katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo (molemmille v�reille)
	if (_lauta[aS][aR] == vk && !getOnkoValkeaKuningasLiikkunut())
	{
		_onkoValkeaKuningasLiikkunut = true;
	}
	else if (_lauta[aS][aR] == mk && !getOnkoMustaKuningasLiikkunut())
	{
		_onkoMustaKuningasLiikkunut = true;
	}

	// katsotaan jos liikkunut nappula on torni niin muutetaan onkoTorniLiikkunut arvo (molemmille v�reille ja molemmille torneille)
	if (_lauta[aS][aR] == vt)
	{
		if (aS == 0 && !getOnkoValkeaDTliikkunut())
		{
			_onkoValkeaDTliikkunut = true;
		}
		else if (aS == 7 && !getOnkoValkeaKTliikkunut())
		{
			_onkoValkeaKTliikkunut = true;
		}
	}
	else if (_lauta[aS][aR] == mt)
	{
		if (aS == 0 && !getOnkoMustaDTliikkunut())
		{
			_onkoMustaDTliikkunut = true;
		}
		else if (aS == 7 && !getOnkoMustaKTliikkunut())
		{
			_onkoMustaKTliikkunut = true;
		}
	}

	// p�ivitet��n _siirtovuoro
	setSiirtovuoro(1 - getSiirtovuoro());
}

int Asema::getSiirtovuoro()
{
	return _siirtovuoro;
}

void Asema::setSiirtovuoro(int vuoro)
{
	_siirtovuoro = vuoro;
}

bool Asema::getOnkoValkeaKuningasLiikkunut()
{
	return _onkoValkeaKuningasLiikkunut;
}

bool Asema::getOnkoMustaKuningasLiikkunut()
{
	return _onkoMustaKuningasLiikkunut;
}

bool Asema::getOnkoValkeaDTliikkunut()
{
	return _onkoValkeaDTliikkunut;
}

bool Asema::getOnkoValkeaKTliikkunut()
{
	return _onkoValkeaKTliikkunut;
}

bool Asema::getOnkoMustaDTliikkunut()
{
	return _onkoMustaDTliikkunut;
}

bool Asema::getOnkoMustaKTliikkunut()
{
	return _onkoMustaKTliikkunut;
}

/* 1. Laske nappuloiden arvo
Daami = 9
Torni = 5
L�hetti = 3,25
Ratsu = 3
Sotilas = 1
2. Kuninkaan hyvyys
Jos avaus tai keskipeli, niin hyv� ett� kunigas g1 tai b1/c1
Loppupeliss� vaikea sanoa halutaanko olla auttamassa omaa sotilasta korottumaan
vai olla est�m�ss� vastustajan korotusta siksi ei oteta kantaa
3. Arvosta keskustaa sotilailla ja ratsuilla
4. Arvosta pitki� linjoja daami, torni ja l�hetti
*/
double Asema::evaluoi()
{
	return 0;

	// kertoimet asetettu sen takia ett� niiden avulla asioiden painoarvoa voidaan s��t�� helposti yhdest� paikasta

	// 1. Nappuloiden arvo

	// 2. Kuningas turvassa

	// 3. Arvosta keskustaa

	// 4. Arvosta linjoja
}

double Asema::laskeNappuloidenArvo(int vari)
{
	return 0;
}

bool Asema::onkoAvausTaiKeskipeli(int vari)
{
	return 0;
	// Jos upseereita 3 tai v�hemm�n on loppupeli
	// mutta jos daami laudalla on loppueli vasta kun kuin vain daami j�ljell�

	// Jos vari on 0 eli valkoiset
	// niin on keskipeli jos mustalla upseereita yli 2 tai jos daami+1
}

double Asema::nappuloitaKeskella(int vari)
{
	return 0;

	// sotilaat ydinkeskustassa + 0.25/napa
	// ratsut ydinkeskustassa + 0.25/napa
	// sotilaat laitakeskustassa + 0.11/napa
	// ratsut laitakeskustassa + 0.11/napa

	// valkeille ydinkeskusta

	// valkeille laitakeskusta

	// mustille ydinkeskusta

	// mustille laitakeskusta
}

double Asema::linjat(int vari)
{
	return 0;

	// valkoiset

	// mustat
}

// https://chessprogramming.wikispaces.com/Minimax MinMax-algoritmin pseudokoodi (lis�sin parametrina aseman)
// int maxi(int depth, asema a)
//	if (depth == 0) return evaluate();
//	int max = -oo;
//	for (all moves ) {
//		score = mini(depth - 1, seuraaja);
//		if (score > max)
//			max = score;
//	}
//	return max;
//}

// int mini(int depth, asema a) {
//	if (depth == 0) return -evaluate();
//	int min = +oo;
//	for (all moves) {
//		score = maxi(depth - 1);
//		if (score < min)
//			min = score;
//	}
//	return min;
// }
MinMaxPaluu Asema::minimax(int syvyys)
{
	MinMaxPaluu paluuarvo;

	// Generoidaan aseman lailliset siirrot.

	// Rekursion kantatapaus 1: peli on loppu

	// Rekursion kantatapaus 2: katkaisusyvyydess�

	// Rekursioaskel: kokeillaan jokaista laillista siirtoa s
	// (alustetaan paluuarvo huonoimmaksi mahdolliseksi).

	return paluuarvo;
}

MinMaxPaluu Asema::maxi(int syvyys)
{
	MinMaxPaluu paluu;
	return paluu;
}

MinMaxPaluu Asema::mini(int syvyys)
{
	MinMaxPaluu paluu;
	return paluu;
}

bool Asema::onkoRuutuUhattu(Ruutu* ruutu, int vastustajanVari)
{
	list<Siirto> vastustajanSiirrot;
	annaLaillisetSiirrot2(vastustajanSiirrot);

	for (Siirto s : vastustajanSiirrot)
	{
		if (s.getLoppuruutu() == *ruutu)
		{
			return true;
		}
	}
	return false;
}

void Asema::huolehdiKuninkaanShakeista(std::list<Siirto> &lista, int vari)
{
	Ruutu kuninkaanRuutu;
	list<Siirto> tempLista;

	for (Siirto s : lista)
	{
		Asema temp = *this;
		temp.paivitaAsema(&s);

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (temp._lauta[j][i] == vk && vari == 0)
				{
					kuninkaanRuutu.setSarake(j);
					kuninkaanRuutu.setRivi(i);
					if (temp.onkoRuutuUhattu(&kuninkaanRuutu, temp._siirtovuoro))
					{
						lista.remove(s);
						//tempLista.push_back(s);
					}
				}
				else if (temp._lauta[j][i] == mk && vari == 1)
				{
					kuninkaanRuutu.setSarake(j);
					kuninkaanRuutu.setRivi(i);
					if (temp.onkoRuutuUhattu(&kuninkaanRuutu, temp._siirtovuoro))
					{
						//tempLista.push_back(s);
						lista.remove(s);
					}
				}
			}
		}
	}
	//lista = tempLista;
}

void Asema::annaLaillisetSiirrot(std::list<Siirto> &lista)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (_lauta[j][i] != NULL && _lauta[j][i]->getVari() == _siirtovuoro)
			{
				_lauta[j][i]->annaSiirrot(lista, new Ruutu(j, i), this, _lauta[j][i]->getVari());
			}
		}
	}
	
	huolehdiKuninkaanShakeista(lista, _siirtovuoro);
}

void Asema::annaLaillisetSiirrot2(std::list<Siirto>& lista)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (_lauta[j][i] != NULL && _lauta[j][i]->getVari() == _siirtovuoro)
			{
				_lauta[j][i]->annaSiirrot(lista, new Ruutu(j, i), this, _lauta[j][i]->getVari());
			}
		}
	}
}