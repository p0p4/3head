#include <iostream>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include "kayttoliittyma.h"
#include "siirto.h"
#include "asema.h"

using namespace std;

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	// SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);

	wcout << "HeippariShakki\n";
	wcout << "Tervetuloa pelaamaan!\n";
	int lopetus = 100;
	Asema asema;
	Kayttoliittyma::getInstance()->aseta_asema(&asema);

	Peli peli(Kayttoliittyma::getInstance()->kysyVastustajanVari());
	std::list<Siirto> lista;
	system("cls");
	int koneenVari = peli.getKoneenVari();

	while (lopetus != 0)
	{
		lista.clear();
		wcout << "\n";
		// Tarkasta onko peli loppu?
		asema.annaLaillisetSiirrot(lista);
		// DEBUG: Lailliset siirrot
		Kayttoliittyma::getInstance()->piirraLauta(lista);
		for (Siirto siirto : lista)
		{
			std::wcout << siirto.getLoppuruutu().getSarake() << " " << siirto.getLoppuruutu().getRivi() << endl;
		}
		if (lista.size() == 0)
		{
			lopetus = 0;
			std::wcout << "Peli loppui";
			continue;
		}

		Siirto siirto;
		// if (asema.getSiirtovuoro() == koneenVari)
		// {
		// 	MinMaxPaluu paluu;
		// 	if (koneenVari == 0)
		// 	{
		// 		paluu = asema.maxi(3);
		// 	}
		// 	else
		// 	{
		// 		paluu = asema.mini(3);
		// 	}
		// 	siirto = paluu._parasSiirto;
		// }
		// else
		// {

		wcout << (asema.getSiirtovuoro() == 0 ? "valkoinen" : "musta") << endl;
		siirto = Kayttoliittyma::getInstance()->annaVastustajanSiirto();
		// }
		asema.paivitaAsema(&siirto);

		wcout << "eval: " << asema.evaluoi() << endl;
	}

	return 0;
}