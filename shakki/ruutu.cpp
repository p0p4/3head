#include "ruutu.h"

Ruutu::Ruutu(int sarake, int rivi)
{
	setSarake(sarake);
	setRivi(rivi);
}

int Ruutu::getRivi()
{
	return _rivi;
}

int Ruutu::getSarake()
{
	return _sarake;
}

void Ruutu::setRivi(int rivi)
{
	_rivi = rivi;
}

void Ruutu::setSarake(int sarake)
{
	_sarake = sarake;
}

bool Ruutu::operator==(const Ruutu& ruutu)
{
	if (_rivi == ruutu._rivi && _sarake == ruutu._sarake)
		return true;
	else
		return false;
}