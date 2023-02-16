#pragma once

// Shakkilaudan ruutu tietyss� (rivi, sarake) -koordinaatissa.
class Ruutu
{
public:
	Ruutu(int, int);
	Ruutu();

	bool operator==(const Ruutu &) const;

	int getRivi();
	int getSarake();
	void setRivi(int);
	void setSarake(int);

private:
	int _sarake;
	int _rivi;
};