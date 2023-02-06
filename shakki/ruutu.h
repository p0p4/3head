#pragma once


// Shakkilaudan ruutu tietyssä (rivi, sarake) -koordinaatissa.
class Ruutu{
public:
	Ruutu(int, int);
	Ruutu() {}
	int getRivi();
	int getSarake();
	void setRivi(int);
	void setSarake(int);
	bool operator==(const Ruutu& ruutu);

private:
	int _sarake;
	int _rivi;
};
