#include <stdio.h>
#define POCETPRVKU 256 //definuje konstantu POCETPRVKU
#define POCETSLOUPCU 8 //definuje konstantu POCETSLOUPCU
#define ZACATEK 14 //definuje konstantu ZACATEK

int main() {
    for (int prvek = ZACATEK; prvek < POCETPRVKU; ++prvek) { //nastavi začátek pomocí konstanty ZACATEK, po každém opakování prvek++. Opakuje kód, pokud je prvek < POCETPRVKU
        printf("%4d %c",prvek,prvek); //vypíše proměnnou prvek jako číslo, poté jako znak (tzn. znak ASCII)
    }
    return 0;
}