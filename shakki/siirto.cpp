#include "siirto.h"

Siirto::Siirto(Ruutu alkuRuutu, Ruutu loppuRuutu)
{
	_alkuRuutu = alkuRuutu;
	_loppuRuutu = loppuRuutu;
	_pitkaLinna = false;
	_lyhytLinna = false;
}

Siirto::Siirto(bool lyhytLinna, bool pitkaLinna)
{
	_lyhytLinna = lyhytLinna;
	_pitkaLinna = pitkaLinna;
}

Ruutu Siirto::getAlkuruutu()
{
	return _alkuRuutu;
}

Ruutu Siirto::getLoppuruutu()
{
	return _loppuRuutu;
}

bool Siirto::onkoLyhytLinna()
{
	return _lyhytLinna;
}

bool Siirto::onkoPitkälinna()
{
	return _pitkaLinna;
}