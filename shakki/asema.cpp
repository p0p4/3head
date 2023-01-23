#include <iostream>
#include "asema.h"
#include "minMaxPaluu.h"
#include "nappula.h"
#include "ruutu.h"

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
	// Ensin alustetaan kaikki laudan ruudut nappulla "NULL", koska muuten ruuduissa satunnaista tauhkaa
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			_lauta[i][j] = NULL;
		}
	}

	// Asetetaan alkuaseman mukaisesti nappulat ruuduille
	_lauta[0][0] = vt;
	_lauta[0][1] = vr;
	_lauta[0][2] = vl;
	_lauta[0][3] = vd;
	_lauta[0][4] = vk;
	_lauta[0][5] = vl;
	_lauta[0][6] = vr;
	_lauta[0][7] = vt;

	for (int i = 0; i < 8; i++)
	{
		_lauta[1][i] = vs;
	}

	_lauta[7][0] = mt;
	_lauta[7][1] = mr;
	_lauta[7][2] = ml;
	_lauta[7][3] = md;
	_lauta[7][4] = mk;
	_lauta[7][5] = ml;
	_lauta[7][6] = mr;
	_lauta[7][7] = mt;

	for (int i = 0; i < 8; i++)
	{
		_lauta[6][i] = ms;
	}
}

void Asema::paivitaAsema(Siirto *siirto)
{
	// Kaksoisaskel-lippu on oletusarvoisesti pois p��lt�.
	// Asetetaan my�hemmin, jos tarvii.

	// Tarkastetaan on siirto lyhyt linna
	if (siirto->_lyhytLinna)
	{
		if (getSiirtovuoro == 0)
		{
			_lauta[0][5] = vk;
			_lauta[0][6] = vt;
			_lauta[0][4] = NULL;
			_lauta[0][7] = NULL;
		}
		else
		{
			_lauta[7][5] = mk;
			_lauta[7][6] = mt;
			_lauta[7][4] = NULL;
			_lauta[7][7] = NULL;
		}
	}

	// onko pitk� linna
	else if (siirto->_pitkaLinna)
	{
		if (getSiirtovuoro == 0)
		{
			_lauta[0][3] = vk;
			_lauta[0][2] = vt;
			_lauta[0][4] = NULL;
			_lauta[0][0] = NULL;
		}
		else
		{
			_lauta[7][3] = mk;
			_lauta[7][2] = mt;
			_lauta[7][4] = NULL;
			_lauta[7][0] = NULL;
		}
	}

	// Kaikki muut siirrot
	else
	{
		// Ottaa siirron alkuruudussa olleen nappulan talteen

		// alku- ja loppurivi
		int aR = siirto->_alkuRivi, lR = siirto->_loppuRivi;
		// alku- ja loppusarake
		int aS = siirto->_alkuSarake, lS = siirto->_loppuSarake;

		// Tarkistetaan oliko sotilaan kaksoisaskel
		// (asetetaan kaksoisaskel-lippu)
		if (_lauta[lR][lS] == vs && lR == 3 && aR == 1)
		{
			kaksoisaskelSarakkeella = lS;
		}
		else if (_lauta[lR][lS] == ms && lR == 4 && aR == 6)
		{
			kaksoisaskelSarakkeella = lS;
		}
		else
		{
			kaksoisaskelSarakkeella = -1;
		}

		// Laittaa talteen otetun nappulan uuteen ruutuun
		_lauta[lR][lS] = _lauta[aR][aS];

		// Ohestaly�nti on tyhj��n ruutuun. Vieress� oleva (sotilas) poistetaan.

		//// Katsotaan jos nappula on sotilas ja rivi on p��tyrivi niin ei vaihdeta nappulaa
		////eli alkuruutuun laitetaan null ja loppuruudussa on jo kliittym�n laittama nappula MIIKKA, ei taida minmaxin kanssa hehkua?

		//
		////muissa tapauksissa alkuruutuun null ja loppuruutuun sama alkuruudusta l�htenyt nappula
		_lauta[aR][aS] = NULL;
	}

	// katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo (molemmille v�reille)
	if (_lauta[lR][lS] == vk)
	{
		_onkoValkeaKuningasLiikkunut = true;
	}
	else if (_lauta[lR][lS] == mk)
	{
		_onkoMustaKuningasLiikkunut = true;
	}

	// katsotaan jos liikkunut nappula on torni niin muutetaan onkoTorniLiikkunut arvo (molemmille v�reille ja molemmille torneille)
	if (_lauta[lR][lS] == vt)
	{
		if (lS == 0)
		{
			_onkoValkeaVTliikkunut = true;
		}
		else if (lS == 7)
		{
			_onkoValkeaOTliikkunut = true;
		}
	}
	else if (_lauta[lR][lS] == mt)
	{
		if (lS == 0)
		{
			_onkoMustaVTliikkunut = true;
		}
		else if (lS == 7)
		{
			_onkoMustaOTliikkunut = true;
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

bool Asema::onkoRuutuUhattu(Ruutu *ruutu, int vastustajanVari)
{

	return false;
}

void Asema::huolehdiKuninkaanShakeista(std::list<Siirto> &lista, int vari)
{
}

void Asema::annaLaillisetSiirrot(std::list<Siirto> &lista)
{
}
