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

bool Siirto::operator==(const Siirto &siirto) const
{
	if (siirto._lyhytLinna == false && siirto._pitkaLinna == false)
	{
		if (_alkuRuutu == siirto._alkuRuutu && _loppuRuutu == siirto._loppuRuutu)
			return true;
		else
			return false;
	}
	else if (siirto._lyhytLinna == _lyhytLinna && siirto._pitkaLinna == _pitkaLinna)
	{
		return true;
	}
	else
	{
		// error with comparison
		return false;
	}
}