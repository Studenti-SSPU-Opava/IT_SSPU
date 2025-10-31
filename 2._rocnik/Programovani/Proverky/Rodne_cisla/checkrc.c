#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELKA 10

// Funkce pro kontrolu rodného čísla
int kontrola(char rodneCislo[]) {
    // Kontrola délky rodného čísla
    if (strlen(rodneCislo) != DELKA) {
        printf("Rodné číslo musí mít %d znaků\n", DELKA);
        return 0;
    }
}

int platne(char rodneCislo[]) {
    // Kontrola, zda je rodné číslo platné
    int den = atoi(strndup(rodneCislo + 4, 2));
    int mesic = atoi(strndup(rodneCislo + 2, 2));
    int rok = atoi(strndup(rodneCislo, 4));

    if (den < 1 || den > 31 || mesic < 1 || mesic > 12) {
        printf("Rodné číslo není platné\n");
        return 0;
    } else {
        printf("Rodné číslo je platné\n");
        printf("Datum narození: %02d.%02d.%04d\n", den, mesic, rok);
    }
}

int main() {
    int opakovani = 1;
    int validni = 0;
    do {
    char rodneCislo[DELKA + 1];
    printf("Zadejte rodné číslo o délce %d:\n", DELKA);
    scanf("%s", rodneCislo);
    validni = kontrola(rodneCislo);
    if (validni) {
        platne(rodneCislo);
    }


    printf("Pro opakování zadejte 1, pro ukončení 0\n");
    scanf("%d", &opakovani);
    } while (opakovani == 1);

}