#include <stdio.h>
#define POCETPRVKU 256 //definuje konstantu POCETPRVKU
#define POCETSLOUPCU 8 //definuje konstantu POCETSLOUPCU
#define ZACATEK 14 //definuje konstantu ZACATEK

int main() {
    int opakovani = 0;
    for (int prvek = ZACATEK; prvek < POCETPRVKU; ++prvek) { //nastavi začátek pomocí konstanty ZACATEK, po každém opakování prvek++. Opakuje kód, pokud je prvek < POCETPRVKU
        printf("%10d %c",prvek,prvek); //vypíše proměnnou prvek jako číslo, poté jako znak (tzn. znak ASCII)
        opakovani++;
        if (opakovani % POCETSLOUPCU ==0) {
            printf("\n");
        }
    }
    return 0;
}