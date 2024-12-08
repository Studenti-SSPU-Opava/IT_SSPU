/*
 * dynamickePole.c ver. 1.0
 *
 * Program pro přečtení uživatelského vstupu
 * a přiřazení jej do dynamického pole 
 * (funguje podobně jako scanf se stringem)
 * =========================================
 *
 * František Rubáček - 16. 10. 2024
 * 
 */
 

#include <stdio.h>
#include <stdlib.h>

char *vstupAZapis(char *znaky, int *pocet) {
    printf("Zadejte retezec znaku:");
    int znak;
    while ((znak = getchar()) != '\n') {
        //vytvoření paměti pro znaky
        znaky = (char *) realloc(znaky, (*pocet + 1) * sizeof(char));
        if (znaky != NULL) {
            //uložení znaku do dynamického pole
            *(znaky + *pocet) = (char) znak;
            (*pocet)++;
        }
    }
    return znaky;
}

void vypis(char *znaky, int pocet) {
    for (int i = 0; i < pocet; ++i) {
        printf("%c", znaky[i]);
    }
    printf("\n");
}

int opakovani() {
    printf("Chcete opakovat zadani? (A/N)");
    char i = 1;
    //Čte vstup uživatele
    scanf("%c", &i);
    //vyprázdní buffer pro další zadání řetězce
    while (getchar() != '\n');
    switch (i) {
        case 'N':
            return 0;
        case 'A':
            return 1;
    }
}

int main() {
    char *znaky = NULL;
    int pocet;
    //opakuje pokud uživatel zadal A pro opakovaní
    do {
        pocet = 0;
        znaky = vstupAZapis(znaky, &pocet);
        vypis(znaky, pocet);
        //vyprázdní alokovanou paměť a odalokuje ji
        free(znaky);
        znaky = NULL;
    } while (opakovani());
    return 0;
}
