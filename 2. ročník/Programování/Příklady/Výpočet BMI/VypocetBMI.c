#include <stdio.h>

#define VSTUPNISOUBOR "vysky_vahy.txt"
#define VYSTUPNISOUBOR "obezita.txt"
#define POCETLIDI 32


typedef struct{
    int vyska;
    int vaha;
}CLOVEK;

int cteniZeSouboru(CLOVEK *lide){
    int i = 0;
    FILE *fptr;
    fptr = fopen(VSTUPNISOUBOR, "r");
    if (fptr == NULL){
        printf("Soubor %s neexistuje nebo neni validni", VSTUPNISOUBOR);

    } else {

        while (fscanf(fptr, "%d%d", &lide[i].vyska, &lide[i].vaha) == 2) {
             i++;
        }
        if (fclose(fptr) == EOF){
            printf("Soubor %s nebyl uspesne uzavren", VSTUPNISOUBOR);
        }
    }
    return i;
}

float vypocet(CLOVEK clovek){
    return (float)clovek.vaha / ((clovek.vyska / 100.0) * (clovek.vyska / 100.0));
}

void zapisDoSouboru(int pocetLidi, CLOVEK *lide){
    int vyskaCelkem = 0;

    FILE *fptr;
    fptr = fopen(VYSTUPNISOUBOR, "w");
    if (fptr == NULL){
        printf("Soubor %s neni validni", VYSTUPNISOUBOR);

    } else {
        int poradi = 1;
        fprintf(fptr, "    O B E Z N I  J E D I N C I\n");
        fprintf(fptr, "---------------------------------\n");
        fprintf(fptr, "poradi|vyska(cm)|vaha(kg)|  BMI |\n");
        fprintf(fptr, "---------------------------------\n");
        for (int i = 0; i < pocetLidi; ++i) {
            if(vypocet(lide[i]) >= 30){
                fprintf(fptr, "%5d.|%9d|%8d|%6.2f|\n", poradi, lide[i].vyska, lide[i].vaha, vypocet(lide[i]));
                poradi++;
            }
        }
        fprintf(fptr, "Do souboru %s byly zapsany udaje o %d obeznich osobach", VYSTUPNISOUBOR, poradi-1);
        printf("Do souboru %s byly zapsany udaje o %d obeznich osobach", VYSTUPNISOUBOR, poradi-1);


        if (fclose(fptr) == EOF){
            printf("Soubor %s nebyl uspesne uzavren", VSTUPNISOUBOR);
        }
    }

}


void vypis(int pocetLidi, CLOVEK *lide){
    int vyskaCelkem = 0;
    printf("  U D A J E  Z E  S O U B O R U\n");
    printf("---------------------------------\n");
    printf("poradi|vyska(cm)|vaha(kg)|  BMI |\n");
    printf("---------------------------------\n");
    for (int i = 0; i < pocetLidi; ++i) {
        vyskaCelkem += lide[i].vyska;
        printf("%5d.|%9d|%8d|%6.2f|\n", i+1, lide[i].vyska, lide[i].vaha, vypocet(lide[i]));
    }
    printf("---------------------------------\n");
    printf("Ze souboru %s byly precteny udaje o %d osobach\n", VSTUPNISOUBOR, pocetLidi);
    printf("Prumerna vyska souboru %d osob je %.2f cm.\n\n", pocetLidi, (float)vyskaCelkem / pocetLidi);
}

int main() {
    int realnyPocetLidi;
    CLOVEK lide[POCETLIDI] ;
    realnyPocetLidi = cteniZeSouboru(lide);
    vypis(realnyPocetLidi, lide);
    zapisDoSouboru(realnyPocetLidi, lide);
    return 0;
}

