#include <iostream>
#include "asema.h"
#include "minmaxpaluu.h"
#include "nappula.h"
#include "ruutu.h"
using namespace std;

Nappula* Asema::vk = new Kuningas(L"\u2654", 0, VK);
Nappula* Asema::vd = new Daami(L"\u2655", 0, VD);
Nappula* Asema::vt = new Torni(L"\u2656", 0, VT);
Nappula* Asema::vl = new Lahetti(L"\u2657", 0, VL);
Nappula* Asema::vr = new Ratsu(L"\u2658", 0, VR);
Nappula* Asema::vs = new Sotilas(L"\u2659", 0, VS);

Nappula* Asema::mk = new Kuningas(L"\u265A", 1, MK);
Nappula* Asema::md = new Daami(L"\u265B", 1, MD);
Nappula* Asema::mt = new Torni(L"\u265C", 1, MT);
Nappula* Asema::ml = new Lahetti(L"\u265D", 1, ML);
Nappula* Asema::mr = new Ratsu(L"\u265E", 1, MR);
Nappula* Asema::ms = new Sotilas(L"\u265F", 1, MS);

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

void Asema::paivitaAsema(Siirto* siirto)
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
	double valkeaArvo = 0;
	double mustaArvo = 0;

	// kertoimet asetettu sen takia ett� niiden avulla asioiden painoarvoa voidaan s��t�� helposti yhdest� paikasta
	double kuningasKerroin = 1;
	double keskustaKerroin = 1;
	double linjaKerroin = 0.05;

	// 1. Nappuloiden arvo
	valkeaArvo += laskeNappuloidenArvo(0);
	mustaArvo += laskeNappuloidenArvo(1);
	wcout << "Nappuloiden arvo: " << valkeaArvo - mustaArvo << endl;

	// 2. Kuningas turvassa
	valkeaArvo += kuningasTurvassa(0) * kuningasKerroin;
	mustaArvo += kuningasTurvassa(1) * kuningasKerroin;
	wcout << "Kuningas turvassa: " << valkeaArvo - mustaArvo << endl;

	// 3. Arvosta keskustaa
	valkeaArvo += nappuloitaKeskella(0) * keskustaKerroin;
	mustaArvo += nappuloitaKeskella(1) * keskustaKerroin;
	wcout << "Keskustan arvo: " << valkeaArvo - mustaArvo << endl;

	// 4. Arvosta linjoja
	//valkeaArvo = linjat(0) * linjaKerroin;
	//mustaArvo = linjat(1) * linjaKerroin;
	//wcout << "Linjojen arvo: " << valkeaArvo - mustaArvo << endl;

	return valkeaArvo - mustaArvo;
}

double Asema::kuningasTurvassa(int vari)
{
	double arvo = 0;

	if (vari == 0 && onkoAvausTaiKeskipeli(0))
	{
		if (_lauta[6][0] != NULL && _lauta[5][1] != NULL && _lauta[6][1] != NULL)
		{
			if (_lauta[6][0] == vk && (_lauta[5][1] == vs && (_lauta[6][1] == vs)))
				arvo += 2;
		}
		if (_lauta[1][0] != NULL && _lauta[2][0] != NULL && _lauta[1][1] != NULL && _lauta[2][1] != NULL)
		{
			if (_lauta[1][0] == vk || _lauta[2][0] == vk && (_lauta[1][1] == vs && (_lauta[2][1] == vs)))
				arvo += 1;
		}
	}
	if (vari == 1 && onkoAvausTaiKeskipeli(1))
	{
		if (_lauta[6][7] != NULL && _lauta[5][6] != NULL && _lauta[6][6] != NULL)
		{
			if (_lauta[6][7] == mk && (_lauta[5][6] == ms && (_lauta[6][6] == ms)))
				arvo += 2;
		}
		if (_lauta[1][7] != NULL && _lauta[2][7] != NULL && _lauta[1][7] != NULL && _lauta[2][7] != NULL)
		{
			if (_lauta[1][7] == mk || _lauta[2][7] == mk && (_lauta[1][7] == ms && (_lauta[2][7] == ms)))
				arvo += 1;
		}
	}

	return arvo;
}

double Asema::laskeNappuloidenArvo(int vari)
{
	double arvo = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (_lauta[i][j] != NULL && vari == _lauta[i][j]->getVari())
			{
				switch (_lauta[i][j]->getKoodi())
				{
				case VD:
				case MD:
					arvo += 9;
					break;
				case VT:
				case MT:
					arvo += 5;
					break;
				case VL:
				case ML:
					arvo += 3.25;
					break;
				case VR:
				case MR:
					arvo += 3;
					break;
				case VS:
				case MS:
					arvo += 1;
					break;
				default:
					break;
				}
			}
		}
	}

	return arvo;
}

bool Asema::onkoAvausTaiKeskipeli(int vari)
{
	int vastustajanVari = 1 - vari;
	int upseeriLkm = 0;
	bool daami = false;

	// Jos upseereita 3 tai v�hemm�n on loppupeli
	// mutta jos daami laudalla on loppueli vasta kun kuin vain daami j�ljell�
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (_lauta[i][j] != NULL && vastustajanVari == _lauta[i][j]->getVari())
			{
				if (_lauta[i][j]->getKoodi() == VD || _lauta[i][j]->getKoodi() == MD)
				{
					daami = true;
				}
				if (_lauta[i][j]->getKoodi() != VS && _lauta[i][j]->getKoodi() != MS)
				{
					upseeriLkm++;
				}
			}
		}
	}

	// Jos vari on 0 eli valkoiset
	// niin on keskipeli jos mustalla upseereita yli 2 tai jos daami+1

	if (upseeriLkm > 2 || (daami == true && upseeriLkm > 1))
		return true;
	else
		return false;
}

double Asema::nappuloitaKeskella(int vari)
{
	double arvo = 0;

	// sotilaat ydinkeskustassa + 0.25/napa
	// ratsut ydinkeskustassa + 0.25/napa
	// sotilaat laitakeskustassa + 0.11/napa
	// ratsut laitakeskustassa + 0.11/napa

	if (_lauta[3][3] != NULL && _lauta[3][3]->getVari() == vari
		&& (_lauta[3][3] == vs || _lauta[3][3] == ms || _lauta[3][3] == vr || _lauta[3][3] == mr))
		arvo += 0.25;

	if (_lauta[4][3] != NULL && _lauta[4][3]->getVari() == vari
		&& (_lauta[4][3] == vs || _lauta[4][3] == ms || _lauta[4][3] == vr || _lauta[4][3] == mr))
		arvo += 0.25;

	if (_lauta[3][4] != NULL && _lauta[3][4]->getVari() == vari
		&& (_lauta[3][4] == vs || _lauta[3][4] == ms || _lauta[3][4] == vr || _lauta[3][4] == mr))
		arvo += 0.25;

	if (_lauta[4][4] != NULL && _lauta[4][4]->getVari() == vari
		&& (_lauta[4][4] == vs || _lauta[4][4] == ms || _lauta[4][4] == vr || _lauta[4][4] == mr))
		arvo += 0.25;

	for (int i = 2; i < 6; i++)
	{
		if (_lauta[i][2] != NULL && _lauta[i][2]->getVari() == vari
			&& (_lauta[i][2] == vs || _lauta[i][2] == ms || _lauta[i][2] == vr || _lauta[i][2] == mr))
			arvo += 0.11;

		if (_lauta[i][5] != NULL && _lauta[i][5]->getVari() == vari
			&& (_lauta[i][5] == vs || _lauta[i][5] == ms || _lauta[i][5] == vr || _lauta[i][5] == mr))
			arvo += 0.11;
	}
	for (int i = 3; i < 5; i++)
	{
		if (_lauta[2][i] != NULL && _lauta[2][i]->getVari() == vari
			&& (_lauta[2][i] == vs || _lauta[2][i] == ms || _lauta[2][i] == vr || _lauta[2][i] == mr))
			arvo += 0.11;

		if (_lauta[5][i] != NULL && _lauta[5][i]->getVari() == vari
			&& (_lauta[5][i] == vs || _lauta[5][i] == ms || _lauta[5][i] == vr || _lauta[5][i] == mr))
			arvo += 0.11;
	}

	return arvo;
}

double Asema::linjat(int vari)
{
	double arvo = 0;

	// valkoiset

	// mustat

	return arvo;
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


	if (getSiirtovuoro() == 0)
	{
		paluuarvo = maxi(syvyys, this);
	}
	else
	{
		paluuarvo = mini(syvyys, this);
	}

	return paluuarvo;
}

MinMaxPaluu Asema::maxi(int syvyys, Asema* a)
{
	MinMaxPaluu paluu;
	MinMaxPaluu temp;
	Ruutu kuninkaanRuutu;

	double max = -100000;

	std::list<Siirto> lista;

	annaLaillisetSiirrot(lista);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (_lauta[j][i] == vk)
			{
				kuninkaanRuutu.setSarake(j);
				kuninkaanRuutu.setRivi(i);
			}
		}
	}

	// Matti ja patti tarkistus
	if (lista.empty() && onkoRuutuUhattu(&kuninkaanRuutu, 0))
	{
		paluu._evaluointiArvo = max;
		return paluu;
	}
	else if (lista.empty())
	{
		paluu._evaluointiArvo = 0;
		return paluu;
	}


	if (syvyys == 0)
	{
		paluu._evaluointiArvo = a->evaluoi();
		return paluu;
	}


	for (Siirto s : lista)
	{
		Asema seuraaja = *a;
		seuraaja.paivitaAsema(&s);
		temp = mini(syvyys - 1, &seuraaja);

		if (temp._evaluointiArvo > max)
		{
			max = temp._evaluointiArvo;
			paluu._evaluointiArvo = temp._evaluointiArvo;
			paluu._parasSiirto = s;
		}
	}

	return paluu;
}

MinMaxPaluu Asema::mini(int syvyys, Asema* a)
{
	MinMaxPaluu paluu;
	MinMaxPaluu temp;
	Ruutu kuninkaanRuutu;

	double min = 100000;

	std::list<Siirto> lista;

	annaLaillisetSiirrot(lista);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (_lauta[j][i] == mk)
			{
				kuninkaanRuutu.setSarake(j);
				kuninkaanRuutu.setRivi(i);
			}
		}
	}

	// Matti ja patti tarkistus
	if (lista.empty() && onkoRuutuUhattu(&kuninkaanRuutu, 1))
	{
		paluu._evaluointiArvo = min;
		return paluu;
	}
	else if (lista.empty())
	{
		paluu._evaluointiArvo = 0;
		return paluu;
	}

	if (syvyys == 0)
	{
		paluu._evaluointiArvo = a->evaluoi();
		return paluu;
	}


	for (Siirto s : lista)
	{
		Asema seuraaja = *a;
		seuraaja.paivitaAsema(&s);
		temp = maxi(syvyys - 1, &seuraaja);

		if (temp._evaluointiArvo < min)
		{
			min = temp._evaluointiArvo;
			paluu._evaluointiArvo = temp._evaluointiArvo;
			paluu._parasSiirto = s;
		}
	}

	return paluu;
}

bool Asema::onkoRuutuUhattu(Ruutu* ruutu, int vastustajanVari)
{
	list<Siirto> vastustajanSiirrot;
	annaVastustajanSiirrot(vastustajanSiirrot);

	for (Siirto s : vastustajanSiirrot)
	{
		if (s.getLoppuruutu() == *ruutu)
		{
			return true;
		}
	}
	return false;
}

void Asema::huolehdiKuninkaanShakeista(std::list<Siirto>& lista, int vari)
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
					if (!temp.onkoRuutuUhattu(&kuninkaanRuutu, temp._siirtovuoro))
					{
						tempLista.push_back(s);
					}
				}
				else if (temp._lauta[j][i] == mk && vari == 1)
				{
					kuninkaanRuutu.setSarake(j);
					kuninkaanRuutu.setRivi(i);
					if (!temp.onkoRuutuUhattu(&kuninkaanRuutu, temp._siirtovuoro))
					{
						tempLista.push_back(s);
					}
				}
			}
		}
	}
	lista = tempLista;
}

void Asema::annaLaillisetSiirrot(std::list<Siirto>& lista)
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
	annaLinnoitusSiirrot(lista, _siirtovuoro);
}

void Asema::annaVastustajanSiirrot(std::list<Siirto>& lista)
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

void Asema::annaLinnoitusSiirrot(std::list<Siirto>& lista, int vari)
{
	int rivi = (vari == 0 ? 0 : 7);
	int vastustajanVari = (vari == 0 ? 1 : 0);

	if ((vari == 0 && !getOnkoValkeaKuningasLiikkunut() && !getOnkoValkeaDTliikkunut() || vari == 1 && !getOnkoMustaKuningasLiikkunut() && !getOnkoMustaDTliikkunut())
		&& _lauta[1][rivi] == NULL
		&& _lauta[2][rivi] == NULL
		&& _lauta[3][rivi] == NULL
		&& !onkoRuutuUhattu(&Ruutu(1, rivi), vastustajanVari)
		&& !onkoRuutuUhattu(&Ruutu(2, rivi), vastustajanVari)
		&& !onkoRuutuUhattu(&Ruutu(3, rivi), vastustajanVari)
		&& !onkoRuutuUhattu(&Ruutu(4, rivi), vastustajanVari))
	{
		lista.push_back(Siirto(false, true));
	}

	if ((vari == 0 && !getOnkoValkeaKuningasLiikkunut() && !getOnkoValkeaKTliikkunut() || vari == 1 && !getOnkoMustaKuningasLiikkunut() && !getOnkoMustaKTliikkunut())
		&& _lauta[6][rivi] == NULL
		&& _lauta[5][rivi] == NULL
		&& !onkoRuutuUhattu(&Ruutu(6, rivi), vastustajanVari)
		&& !onkoRuutuUhattu(&Ruutu(5, rivi), vastustajanVari)
		&& !onkoRuutuUhattu(&Ruutu(4, rivi), vastustajanVari))
	{
		lista.push_back(Siirto(true, false));
	}
}