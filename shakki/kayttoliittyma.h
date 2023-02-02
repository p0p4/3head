#pragma once
#include "asema.h"
#include "nappula.h"
#include "peli.h"
#include "siirto.h"

// Shakkiohjelman k�ytt�liittym�, joka osaa visualisoida nykyisen aseman
// ja lukea k�ytt�j�n sy�tt�m�t siirrot. Singleton.
class Kayttoliittyma
{
public:
	void aseta_asema(Asema *asema) { this->_asema = asema; }
	void piirraLauta(std::list<Siirto> &lista);
	Siirto annaVastustajanSiirto();
	int kysyVastustajanVari();

	static Kayttoliittyma *getInstance();

private:
	Asema *_asema;
	static Kayttoliittyma *instance; // osoitin luokan ainoaan olioon (Singleton).

	Kayttoliittyma() {}
	Kayttoliittyma(Asema *asema) { this->_asema = asema; }
};
