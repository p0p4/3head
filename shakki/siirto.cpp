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
	if (lyhytLinna && pitkaLinna)
		return;

	_lyhytLinna = lyhytLinna;
	_pitkaLinna = pitkaLinna;
	_alkuRuutu = Ruutu(0, 0);
	_loppuRuutu = Ruutu(0, 0);
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

bool Siirto::onkoPitkalinna()
{
	return _pitkaLinna;
}