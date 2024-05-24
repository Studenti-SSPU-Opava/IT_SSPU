#include <stdio.h>

#define CISLA "cisla.txt"
#define VYSTUP "vystup.txt"

typedef struct {
    int zaklad;
    int exponent;
    int mocnina;
} CISLO;

void hlavickaProgram(){
    printf("Vypis cisel ze souboru %s\n", CISLA);
    printf("--------------------------------\n");
    printf("poradi  zaklad  exponent  mocnina\n");
}

void hlavickaVystup(FILE *vystup){
    fprintf(vystup, "Vypis cisel s prvociselnym zakladem ze souboru %s\n", CISLA);
    fprintf(vystup, "--------------------------------------------------------\n");
}

int mocnina(int zaklad, int exponent){
    int vysledek = 1;
    for (int i = 0; i < exponent; i++) {
        vysledek *= zaklad;
    }
    return vysledek;
}

int main(){
    FILE *cisla;
    FILE *vystup;
    CISLO cislo;
    int poradi = 0;

    if ((cisla = fopen(CISLA, "r")) == NULL) {
        printf("File %s has had an error opening.\n", CISLA);
    } else {
        if ((vystup = fopen(VYSTUP, "w")) == NULL) {
            printf("File %s has had an error opening.\n", VYSTUP);
        }
        hlavickaProgram();
        while (fscanf(cisla, "%5d%5d", &cislo.zaklad, &cislo.exponent) == 2) {
            poradi++;
            printf("%5d.   %5d     %5d    %5d\n", poradi, cislo.zaklad, cislo.exponent, mocnina(cislo.zaklad, cislo.exponent));
            hlavickaVystup(vystup);
            //fprintf(vystup, "%5d.   %5d     %5d    %5d\n", poradi, cislo.zaklad, cislo.exponent, mocnina(cislo.zaklad, cislo.exponent));
        }















        if (fclose(cisla) == EOF) {
            printf("The file %s has had an error closing.\n", CISLA);
        }
        if (fclose(vystup) == EOF) {
            printf("The file %s has had an error closing.\n",VYSTUP);
        } else {
            printf("The file %s has been created with pairs of numbers equal to %d.\n", VYSTUP, poradi);
        }
    }
    return 0;
}