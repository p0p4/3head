#include <iostream>
#include "asema.h"
#include "minmaxpaluu.h"
#include "nappula.h"
#include "ruutu.h"
#include <chrono>

using namespace std;

Nappula *Asema::vk = new Kuningas(L"\u2654", 0, VK);
Nappula *Asema::vd = new Daami(L"\u2655", 0, VD);
Nappula *Asema::vt = new Torni(L"\u2656", 0, VT);
Nappula *Asema::vl = new Lahetti(L"\u2657", 0, VL);
Nappula *Asema::vr = new Ratsu(L"\u2658", 0, VR);
Nappula *Asema::vs = new Sotilas(L"\u2659", 0, VS);

// Nappula *Asema::vk = new Kuningas(L"\u265A", 0, VK);
// Nappula *Asema::vd = new Daami(L"\u265B", 0, VD);
// Nappula *Asema::vt = new Torni(L"\u265C", 0, VT);
// Nappula *Asema::vl = new Lahetti(L"\u265D", 0, VL);
// Nappula *Asema::vr = new Ratsu(L"\u265E", 0, VR);
// Nappula *Asema::vs = new Sotilas(L"\u265F", 0, VS);

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

	ihmisenVuoro = false;
	valkeidenUpseerienLkm = 6;
	mustienUpseerienLkm = 6;
	valkeaDaami = true;
	mustaDaami = true;

	valkeanKuninkaanRuutu.setSarake(4);
	valkeanKuninkaanRuutu.setRivi(0);

	mustanKuninkaanRuutu.setSarake(4);
	mustanKuninkaanRuutu.setRivi(7);

}

void Asema::paivitaAsema(Siirto *siirto)
{
	int aS, aR;
	int lS, lR;

	aS = siirto->getAlkuruutu().getSarake();
	aR = siirto->getAlkuruutu().getRivi();

	lS = siirto->getLoppuruutu().getSarake();
	lR = siirto->getLoppuruutu().getRivi();

	// katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo (molemmille v�reille)
	//if (_lauta[aS][aR] == vk && !getOnkoValkeaKuningasLiikkunut())
	//{
	//	_onkoValkeaKuningasLiikkunut = true;
	//}
	//else if (_lauta[aS][aR] == mk && !getOnkoMustaKuningasLiikkunut())
	//{
	//	_onkoMustaKuningasLiikkunut = true;
	//}

	// katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo (molemmille v�reille)
	// ja päivittää kuninkaan ruudun
	if (_lauta[aS][aR] == vk)
	{
		valkeanKuninkaanRuutu.setSarake(lS);
		valkeanKuninkaanRuutu.setRivi(lR);

		if (!getOnkoValkeaKuningasLiikkunut())
		{
			_onkoValkeaKuningasLiikkunut = true;
		}
	}
	else if (_lauta[aS][aR] == mk)
	{
		mustanKuninkaanRuutu.setSarake(lS);
		mustanKuninkaanRuutu.setRivi(lR);

		if (!getOnkoMustaKuningasLiikkunut())
		{
			_onkoMustaKuningasLiikkunut = true;
		}
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
			if (_lauta[aS][aR] == vs && lS == kaksoisaskelSarakkeella && aR == 4)
			{
				_lauta[lS][lR - 1] = NULL;
			}
			else if (_lauta[aS][aR] == ms && lS == kaksoisaskelSarakkeella && aR == 3)
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
		else if (_lauta[aS][aR] == vs && lR == 7 || _lauta[aS][aR] == ms && lR == 0)
		{
			// Sotilaan korotukset
			if (ihmisenVuoro)
			{
				string korotus;

				wcout << "Miksi korotetaan? (D, T, L, R)" << endl;
				cin >> korotus;

				if (korotus == "D")
				{
					if (_siirtovuoro == 0)
					{
						siirto->_miksikorotetaan = vd;
					}
					else
					{
						siirto->_miksikorotetaan = md;
					}
				}
				else if (korotus == "T")
				{
					if (_siirtovuoro == 0)
					{
						siirto->_miksikorotetaan = vt;
					}
					else
					{
						siirto->_miksikorotetaan = mt;
					}
				}
				else if (korotus == "L")
				{
					if (_siirtovuoro == 0)
					{
						siirto->_miksikorotetaan = vl;
					}
					else
					{
						siirto->_miksikorotetaan = ml;
					}
				}
				else if (korotus == "R")
				{
					if (_siirtovuoro == 0)
					{
						siirto->_miksikorotetaan = vr;
					}
					else
					{
						siirto->_miksikorotetaan = mr;
					}
				}
			}

			_lauta[lS][lR] = siirto->_miksikorotetaan;
		}

		_lauta[aS][aR] = NULL;
	}

	// p�ivitet��n _siirtovuoro
	setSiirtovuoro(1 - getSiirtovuoro());
	ihmisenVuoro = false;
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
	double linjaKerroin = 0.1;

	if (!onkoAvausTaiKeskipeli(0) || !onkoAvausTaiKeskipeli(1))
	{
		keskustaKerroin = keskustaKerroin * 0.3;
		linjaKerroin = linjaKerroin * 0.5;
	}

	// 1. Nappuloiden arvo
	valkeaArvo += laskeNappuloidenArvo(0);
	mustaArvo += laskeNappuloidenArvo(1);
	// wcout << "Nappuloiden arvo: " << valkeaArvo - mustaArvo << endl;

	// 2. Kuningas turvassa
	valkeaArvo += kuningasTurvassa(0) * kuningasKerroin;
	mustaArvo += kuningasTurvassa(1) * kuningasKerroin;
	// wcout << "Kuningas turvassa: " << valkeaArvo - mustaArvo << endl;


	// 3. Arvosta keskustaa
	valkeaArvo += nappuloitaKeskella(0) * keskustaKerroin;
	mustaArvo += nappuloitaKeskella(1) * keskustaKerroin;
	// wcout << "Keskustan arvo: " << valkeaArvo - mustaArvo << endl;

	// 4. Arvosta linjoja
	valkeaArvo += linjat(0) * linjaKerroin;
	mustaArvo += linjat(1) * linjaKerroin;
	// wcout << "Linjojen arvo: " << valkeaArvo - mustaArvo << endl;

	valkeaArvo += ratsujaReunoilla(0);
	mustaArvo += ratsujaReunoilla(1);

	valkeaArvo += sotilaat(0);
	mustaArvo += sotilaat(1);

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
				if (_lauta[i][j] == vd || _lauta[i][j] == md)
				{
					daami = true;
				}
				if (_lauta[i][j] != vs && _lauta[i][j] != ms && _lauta[i][j] != vk && _lauta[i][j] != mk && _lauta[i][j] != vd && _lauta[i][j] != md)
				{
					upseeriLkm++;
				}
			}
		}
	}

	if (vari == 0)
	{
		mustienUpseerienLkm = upseeriLkm;
		mustaDaami = daami;
	}
	else if (vari == 1)
	{
		valkeidenUpseerienLkm = upseeriLkm;
		valkeaDaami = daami;
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
	// 4. Arvosta pitkiä linjoja daami, torni ja lähetti
	double arvo = 0;
	double daamiArvo = 0;
	std::list<Siirto> lista;
	std::list<Siirto> daamiLista;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (_lauta[i][j] == NULL || _lauta[i][j]->getVari() != vari)
				continue;

			Ruutu ruutu(i, j);

			if (_lauta[i][j] == vl || _lauta[i][j] == ml)
			{
				_lauta[i][j]->annaSiirrot(lista, &ruutu, this, vari);
			}
			else if (_lauta[i][j] == vt || _lauta[i][j] == mt)
			{
				_lauta[i][j]->annaSiirrot(lista, &ruutu, this, vari);
			}
			else if ((!onkoAvausTaiKeskipeli(0) && _lauta[i][j] == vd) || (!onkoAvausTaiKeskipeli(1) && _lauta[i][j] == md))
			{
				_lauta[i][j]->annaSiirrot(daamiLista, &ruutu, this, vari);
				daamiArvo = daamiLista.size() / 2;
			}
		}
	}
	arvo = lista.size() + daamiArvo;

	return arvo;
}

// arvostaa sotilata jotka suojaavat toisaan
// ja sotilaita jotka ovat liikkuneet pidemmälle (loppupelissä enemmän)
// kaksois sotilaista pisteitä pois
double Asema::sotilaat(int vari)
{
	int kaksoisSotilaat = 0;
	double arvo = 0;

	if (vari == 0)
	{
		for (int i = 0; i < 7; i++)
		{
			for (int j = 1; j < 6; j++)
			{
				if (_lauta[i][j] != NULL && _lauta[i][j] == vs)
				{
					kaksoisSotilaat++;

					if ((i < 7 && _lauta[i + 1][j - 1] != NULL && _lauta[i + 1][j - 1] == vs) || (i > 0 && _lauta[i - 1][j - 1] != NULL && _lauta[i - 1][j - 1] == vs))
					{
						arvo += 0.05;
					}

					if (_lauta[i][j] != NULL && _lauta[i][j] == vs)
					{
						arvo += (j - 1) * 0.04;

						if (onkoAvausTaiKeskipeli(0))
						{
							arvo += (j - 1) * 0.05;

							if (!mustaDaami && mustienUpseerienLkm < 2)
							{
								arvo += (j - 1) * 0.07;
							}
						}
					}
				}
			}

			if (kaksoisSotilaat > 1)
			{
				arvo += kaksoisSotilaat * 0.2;
			}

			kaksoisSotilaat = 0;
		}
	}

	if (vari == 1)
	{
		for (int i = 0; i < 7; i++)
		{
			for (int j = 1; j < 6; j++)
			{
				if (_lauta[i][j] != NULL && _lauta[i][j] == ms)
				{
					kaksoisSotilaat++;

					if ((i < 7 && _lauta[i + 1][j + 1] != NULL && _lauta[i + 1][j + 1] == ms) || (i < 0 && _lauta[i - 1][j + 1] != NULL && _lauta[i - 1][j + 1] == ms))
					{
						arvo += 0.05;
					}
				}

				if (_lauta[i][j] != NULL && _lauta[i][j] == ms)
				{
					arvo += (6 - j) * 0.04;

					if (onkoAvausTaiKeskipeli(0))
					{
						arvo += (6 - j) * 0.05;

						if (!valkeaDaami && valkeidenUpseerienLkm < 2)
						{
							arvo += (6 - j) * 0.07;
						}
					}
				}
			}

			if (kaksoisSotilaat > 1)
			{
				arvo += kaksoisSotilaat * 0.2;
			}

			kaksoisSotilaat = 0;
		}
	}


	return arvo;
}


// -0.11 jokaisesta ratsusta joka on pelilaudan reunalla.
double Asema::ratsujaReunoilla(int vari)
{
	double arvo = 0;

	for (int i = 0; i < 8; i++)
	{
		if (_lauta[0][i] != NULL && _lauta[0][i]->getVari() == vari && (_lauta[0][i] == vr || _lauta[0][i] == mr))
		{
			arvo -= 0.11;
		}
	}

	for (int i = 0; i < 8; i++)
	{
		if (_lauta[7][i] != NULL && _lauta[7][i]->getVari() == vari && (_lauta[0][i] == vr || _lauta[0][i] == mr))
		{
			arvo -= 0.11;
		}
	}

	for (int j = 0; j < 8; j++)
	{
		if (_lauta[j][0] != NULL && _lauta[j][0]->getVari() == vari && (_lauta[j][0] == vr || _lauta[j][0] == mr))
		{
			arvo -= 0.11;
		}
	}

	for (int j = 0; j < 8; j++)
	{
		if (_lauta[j][7] != NULL && _lauta[j][7]->getVari() == vari && (_lauta[j][7] == vr || _lauta[j][7] == mr))
		{
			arvo -= 0.11;
		}
	}

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

	double alpha = -100000;
	double beta = 100000;

	//auto start_time = std::chrono::high_resolution_clock::now();

	if (getSiirtovuoro() == 0)
	{
		paluuarvo = maxi(syvyys, this, alpha, beta);
	}
	else
	{
		paluuarvo = mini(syvyys, this, alpha, beta);
	}

	//auto end_time = std::chrono::high_resolution_clock::now();
 //   auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

 //   std::cout << "Elapsed time: " << elapsed_time << " ms" << std::endl;

	return paluuarvo;
}

MinMaxPaluu Asema::maxi(int syvyys, Asema *a, double alpha, double beta)
{
    MinMaxPaluu paluu;

	if (syvyys == 0)
	{
		paluu._evaluointiArvo = a->evaluoi();
		return paluu;
	}

    MinMaxPaluu temp;
    std::list<Siirto> lista;

    a->annaLaillisetSiirrot(lista);

	//Ruutu kuninkaanRuutu;
    //for (int i = 0; i < 8; i++)
    //{
    //    for (int j = 0; j < 8; j++)
    //    {
    //        if (a->_lauta[j][i] == vk)
    //        {
    //            kuninkaanRuutu.setSarake(j);
    //            kuninkaanRuutu.setRivi(i);
    //        }
    //    }
    //}

    if (lista.empty() && a->onkoRuutuUhattu(&valkeanKuninkaanRuutu, 1))
    {
        paluu._evaluointiArvo = -100000;
        return paluu;
    }
    else if (lista.empty())
    {
        paluu._evaluointiArvo = 0;
        return paluu;
    }

    double max = -100000;

    for (Siirto s : lista)
    {
        Asema seuraaja = *a;
        seuraaja.paivitaAsema(&s);

        temp = mini(syvyys - 1, &seuraaja, alpha, beta);

        if (temp._evaluointiArvo > max)
        {
            max = temp._evaluointiArvo;
            paluu._evaluointiArvo = temp._evaluointiArvo;
            paluu._parasSiirto = s;
        }

        if (max >= beta)
            break;

        if (max > alpha)
            alpha = max;
    }

    return paluu;
}

MinMaxPaluu Asema::mini(int syvyys, Asema *a, double alpha, double beta)
{
    MinMaxPaluu paluu;

	if (syvyys == 0)
	{
		paluu._evaluointiArvo = a->evaluoi();
		return paluu;
	}


    MinMaxPaluu temp;
    std::list<Siirto> lista;

    a->annaLaillisetSiirrot(lista);


	//Ruutu kuninkaanRuutu;
    //for (int i = 0; i < 8; i++)
    //{
    //    for (int j = 0; j < 8; j++)
    //    {
    //        if (a->_lauta[j][i] == mk)
    //        {
    //            kuninkaanRuutu.setSarake(j);
    //            kuninkaanRuutu.setRivi(i);
    //        }
    //    }
    //}

    if (lista.empty() && a->onkoRuutuUhattu(&mustanKuninkaanRuutu, 0))
    {
        paluu._evaluointiArvo = 100000;
        return paluu;
    }
    else if (lista.empty())
    {
        paluu._evaluointiArvo = 0;
        return paluu;
    }

    double min = 100000;

    for (Siirto s : lista)
    {
        Asema seuraaja = *a;
        seuraaja.paivitaAsema(&s);

        temp = maxi(syvyys - 1, &seuraaja, alpha, beta);

        if (temp._evaluointiArvo < min)
        {
            min = temp._evaluointiArvo;
            paluu._evaluointiArvo = temp._evaluointiArvo;
            paluu._parasSiirto = s;
        }

        if (min <= alpha)
            return paluu;

        if (min < beta)
            beta = min;
    }

    return paluu;
}

bool Asema::onkoRuutuUhattu(Ruutu *ruutu, int vastustajanVari)
{
	list<Siirto> vastustajanSiirrot;
	annaVastustajanSiirrot(vastustajanSiirrot, vastustajanVari);

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
	list<Siirto> tempLista;

	//Ruutu kuninkaanRuutu;

	//if (vari == 0)
	//{
	//	kuninkaanRuutu = valkeanKuninkaanRuutu;
	//}
	//else if (vari == 1)
	//{
	//	kuninkaanRuutu = mustanKuninkaanRuutu;
	//}

	//for (Siirto s : lista)
	//{
	//	Asema temp = *this;
	//	temp.paivitaAsema(&s);

	//	for (int i = 0; i < 8; i++)
	//	{
	//		for (int j = 0; j < 8; j++)
	//		{
	//			if (temp._lauta[j][i] == vk && vari == 0)
	//			{
	//				kuninkaanRuutu.setSarake(j);
	//				kuninkaanRuutu.setRivi(i);
	//				if (!temp.onkoRuutuUhattu(&kuninkaanRuutu, temp._siirtovuoro))
	//				{
	//					tempLista.push_back(s);
	//				}
	//			}
	//			else if (temp._lauta[j][i] == mk && vari == 1)
	//			{
	//				kuninkaanRuutu.setSarake(j);
	//				kuninkaanRuutu.setRivi(i);
	//				if (!temp.onkoRuutuUhattu(&kuninkaanRuutu, temp._siirtovuoro))
	//				{
	//					tempLista.push_back(s);
	//				}
	//			}
	//		}
	//	}
	//}

	for (Siirto s : lista)
	{
		Asema temp = *this;
		temp.paivitaAsema(&s);

		if (vari == 0 && !temp.onkoRuutuUhattu(&temp.valkeanKuninkaanRuutu, temp._siirtovuoro))
		{
			tempLista.push_back(s);
		}
		else if (vari == 1 && !temp.onkoRuutuUhattu(&temp.mustanKuninkaanRuutu, temp._siirtovuoro))
		{
			tempLista.push_back(s);
		}
	}

	lista = tempLista;
}

void Asema::annaLaillisetSiirrot(std::list<Siirto> &lista)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (_lauta[j][i] != NULL && _lauta[j][i]->getVari() == _siirtovuoro)
			{
				Ruutu ruutu(j, i);
				_lauta[j][i]->annaSiirrot(lista, &ruutu, this, _lauta[j][i]->getVari());
			}
		}
	}

	huolehdiKuninkaanShakeista(lista, _siirtovuoro);
	annaLinnoitusSiirrot(lista, _siirtovuoro);
}

void Asema::annaVastustajanSiirrot(std::list<Siirto> &lista, int vastustajanVari)
{
	//int vastustajanVari = (_siirtovuoro == 0 ? 1 : 0);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (_lauta[j][i] != NULL && _lauta[j][i]->getVari() == vastustajanVari)
			{
				Ruutu ruutu(j, i);
				_lauta[j][i]->annaSiirrot(lista, &ruutu, this, _lauta[j][i]->getVari());
			}
		}
	}
}

void Asema::annaLinnoitusSiirrot(std::list<Siirto> &lista, int vari)
{
	int rivi = (vari == 0 ? 0 : 7);
	int vastustajanVari = (vari == 0 ? 1 : 0);

	Ruutu ruutu1(1, rivi);
	Ruutu ruutu2(2, rivi);
	Ruutu ruutu3(3, rivi);
	Ruutu ruutu4(4, rivi);
	Ruutu ruutu5(5, rivi);
	Ruutu ruutu6(6, rivi);

	if ((vari == 0 && !getOnkoValkeaKuningasLiikkunut() && !getOnkoValkeaDTliikkunut() || vari == 1 && !getOnkoMustaKuningasLiikkunut() && !getOnkoMustaDTliikkunut())
	&& _lauta[1][rivi] == NULL
	&& _lauta[2][rivi] == NULL
	&& _lauta[3][rivi] == NULL
	&& !onkoRuutuUhattu(&ruutu1, vastustajanVari)
	&& !onkoRuutuUhattu(&ruutu2, vastustajanVari)
	&& !onkoRuutuUhattu(&ruutu3, vastustajanVari)
	&& !onkoRuutuUhattu(&ruutu4, vastustajanVari))
	{
		lista.push_back(Siirto(false, true));
	}

	if ((vari == 0 && !getOnkoValkeaKuningasLiikkunut() && !getOnkoValkeaKTliikkunut() || vari == 1 && !getOnkoMustaKuningasLiikkunut() && !getOnkoMustaKTliikkunut())
	&& _lauta[6][rivi] == NULL
	&& _lauta[5][rivi] == NULL
	&& !onkoRuutuUhattu(&ruutu6, vastustajanVari)
	&& !onkoRuutuUhattu(&ruutu5, vastustajanVari)
	&& !onkoRuutuUhattu(&ruutu4, vastustajanVari))
	{
		lista.push_back(Siirto(true, false));
	}
}