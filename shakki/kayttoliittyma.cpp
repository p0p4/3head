﻿#include <Windows.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include "kayttoliittyma.h"

using namespace std;

Kayttoliittyma *Kayttoliittyma::instance = 0;

Kayttoliittyma *Kayttoliittyma::getInstance()
{
    if (instance == 0)
        instance = new Kayttoliittyma();
    return instance;
}

void Kayttoliittyma::piirraLauta(std::list<Siirto> &lista)
{
    // Asetetaan konsoliin UTF-8
    _setmode(_fileno(stdout), _O_U16TEXT);

    // Piirret��n lauta
    for (int i = 7; i >= 0; i--)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        wcout << i + 1 << L" ";

        for (int j = 0; j < 8; j++)
        {
            Nappula *nappula = _asema->_lauta[j][i];

            if ((i + j) % 2 == 0)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 128);
            }

            // DEBUG: Lailliset siirrot
            for (Siirto siirto : lista)
            {
                if (siirto.getLoppuruutu().getSarake() == j && siirto.getLoppuruutu().getRivi() == i)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 160);
                }
            }

            if (nappula == 0)
                wcout << L"   ";
            else
                wcout << " " << nappula->getUnicode() << " ";
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
        wcout << L".\n";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    wcout << L"   a  b  c  d  e  f  g  h \n";
}

/*
    Aliohjelma tarkistaa että käyttäjän antama syöte siirroksi on
    muodollisesti korrekti (ei tarkista aseman laillisuutta)
    Ottaa irti myös nappulan kirjaimen (K/D/L/R/T), tarkistaa että kirjain korrekti
*/
Siirto Kayttoliittyma::annaVastustajanSiirto(std::list<Siirto>& lista)
{
    Ruutu alku;
    Ruutu loppu;
    Siirto siirto;

    int asciiConversionChar = 97;
    int asciiConversionNum = 49;

    wcout << "Anna siirto." << endl;
    string siirtoStr;
    cin >> siirtoStr;

    while (siirtoStr.length() > 6 || (siirtoStr.length() < 5 && siirtoStr.length() != 3))
    {
        wcout << "Virheellinen siirto." << endl;

        wcout << "Anna siirto." << endl;
        cin >> siirtoStr;
    }

    if (siirtoStr.length() == 6)
    {
        alku.setSarake(int(siirtoStr[1]) - asciiConversionChar);
        alku.setRivi((int)siirtoStr[2] - asciiConversionNum);

        loppu.setSarake(int(siirtoStr[4]) - asciiConversionChar);
        loppu.setRivi((int)siirtoStr[5] - asciiConversionNum);

        if ((alku.getRivi() < 0 || alku.getRivi() > 7) || (alku.getSarake() < 0 || alku.getSarake() > 7) || (loppu.getRivi() < 0 || loppu.getRivi() > 7) || (loppu.getSarake() < 0 || loppu.getSarake() > 7))
        {
            wcout << "Virheellinen siirto." << endl;
            siirto = annaVastustajanSiirto(lista);
            return siirto;
        }

        Siirto siirtoTemp(alku, loppu);
        siirto = siirtoTemp;
    }
    else if (siirtoStr.length() == 5 && siirtoStr[0] != 'O' && siirtoStr[0] != 'o')
    {
        alku.setSarake(int(siirtoStr[0]) - asciiConversionChar);
        alku.setRivi((int)siirtoStr[1] - asciiConversionNum);

        loppu.setSarake(int(siirtoStr[3]) - asciiConversionChar);
        loppu.setRivi((int)siirtoStr[4] - asciiConversionNum);

        if ((alku.getRivi() < 0 || alku.getRivi() > 7) || (alku.getSarake() < 0 || alku.getSarake() > 7) || (loppu.getRivi() < 0 || loppu.getRivi() > 7) || (loppu.getSarake() < 0 || loppu.getSarake() > 7))
        {
            wcout << "Virheellinen siirto." << endl;
            siirto = annaVastustajanSiirto(lista);
            return siirto;
        }

        Siirto siirtoTemp(alku, loppu);
        siirto = siirtoTemp;
    }
    else if (siirtoStr == "O-O-O" || siirtoStr == "o-o-o")
    {
        Siirto siirtoTemp(false, true);
        siirto = siirtoTemp;
    }
    else if (siirtoStr == "O-O" || siirtoStr == "o-o")
    {
        Siirto siirtoTemp(true, false);
        siirto = siirtoTemp;
    }


    // tarkistaa, että siirto on laillinen
    //for(Siirto &s : lista)
    //{
    //    if (s == siirto)
    //    {
    //        return siirto;
    //    }
    //}
    //siirto = annaVastustajanSiirto(lista);

    return siirto;
}

int Kayttoliittyma::kysyVastustajanVari()
{
    return 0;
}