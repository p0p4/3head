#include "siirto.h"

Siirto::Siirto(Ruutu alkuRuutu, Ruutu loppuRuutu)
{
	_alkuRuutu = alkuRuutu;
	_loppuRuutu = loppuRuutu;
}

Siirto::Siirto(bool lyhytLinna, bool pitkaLinna)
{
	_lyhytLinna = lyhytLinna;
	_pitkaLinna = pitkaLinna;
}

Siirto::Siirto()
{
	_alkuRuutu = Ruutu(0, 0);
	_loppuRuutu = Ruutu(0, 0);
	_lyhytLinna = false;
	_pitkaLinna = false;
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

bool Siirto::onkoPitk�linna()
{
	return _pitkaLinna;
}