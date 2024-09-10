#include <stdio.h>

#define JMENOSOUBORU "vysky_vahy.txt"
#define POCETLIDI 32


typedef struct{
    int vyska;
    int vaha;
}CLOVEK;

int cteniZeSouboru(CLOVEK *lide){
    int i = 0;
    FILE *fptr;
    fptr = fopen(JMENOSOUBORU, "r");
    if (fptr == NULL){
        printf("Soubor %s neexistuje nebo neni validni", JMENOSOUBORU);

    } else {

        while (fscanf(fptr, "%d%d", &lide[i].vyska, &lide[i].vaha) == 2) {
             i++;
        }
        if (fclose(fptr) == EOF){
            printf("Soubor %s nebyl uspesne uzavren", JMENOSOUBORU);
        }
    }
    return i;
}

int zapisDoSouboru(){

}

float vypocet(CLOVEK clovek){
    return (float)clovek.vaha / ((clovek.vyska / 100.0) * (clovek.vyska / 100.0));
}

void vypis(int pocetLidi, CLOVEK *lide){

    for (int i = 0; i < pocetLidi; ++i) {
        printf("%2d | %3d | %3d | %6.2f \n", i+1, lide[i].vyska, lide[i].vaha, vypocet(lide[i]));
    }
}

int main() {
    int realnyPocetLidi;
    CLOVEK lide[POCETLIDI] ;
    realnyPocetLidi = cteniZeSouboru(lide);
    vypis(realnyPocetLidi, lide);
    return 0;
}

