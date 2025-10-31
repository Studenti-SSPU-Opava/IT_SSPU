/*
 * trideniCasu.c ver. 1.0
 *
 * Převedení 24 hodinového času na 12 hodinový 
 * ===========================================
 *
 * v1.0 - Matěj Pika - 23.10.2024
 * 
*/


#include <stdio.h>
#include <stdlib.h>

#define VSTUPNISOUBOR "casy.txt"

typedef struct {
    int hod;
    int min;
    int sec;
} CAS;

CAS *cteni(CAS *casy, int *pocet) {
    FILE *soubor = fopen(VSTUPNISOUBOR, "r");

    if (soubor == NULL) {
        printf("Soubor %s se nepodarilo otevrit.\n", VSTUPNISOUBOR);
    } else {
        casy = (CAS *) malloc(sizeof(CAS));
        if (casy == NULL) {
            printf("Nepodarilo se alokovat pamet.\n");
            return NULL;
        }
        while (fscanf(soubor, "%d:%d:%d", &casy[*pocet].hod, &casy[*pocet].min, &casy[*pocet].sec) == 3) {
            casy = (CAS *) realloc(casy, sizeof(CAS) * (*pocet) + 1);
            if (casy == NULL) {
                printf("Nepodarilo se realokovat pamet.\n");
                free(casy);
                casy = NULL;
                break;
            }
            (*pocet)++;
        }
    }

    if (fclose(soubor) == EOF) {
        printf("Soubor %s se nepodarilo zavrit.\n", VSTUPNISOUBOR);
    }
    return casy;
}

int main() {
    CAS *casy = NULL;
    int pocet = 0;
    casy = cteni(casy, &pocet);
    free(casy);
}
