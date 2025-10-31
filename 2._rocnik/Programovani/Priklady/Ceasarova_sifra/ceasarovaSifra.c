/*
 * ceasarovaSifra.c ver. 1.0
 *
 * Program na sifrovani a desifrovani textu
 * ========================================
 *
 * v1.0 - František Rubáček - 26.02.2025
 * 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include  <ctype.h>

#define MIN 0
#define MAX 26

char *vstup(char *text) {
    printf("Zadej zasifrovatelnou zpravu. \n");
    int pocetZnaku = 0;
    int znak;
    while ((znak = getchar()) != '\n') {
        text = (char *) realloc(text, (pocetZnaku + 1) * sizeof(char));
        if (text != NULL) {
            text[pocetZnaku] = (char) znak;
            pocetZnaku++;
        } else {
            printf("Chyba realokace pametoveho bloku. \n");
            break;
        }
    }
    if (text != NULL) {
        text = (char *) realloc(text, (pocetZnaku + 1) * sizeof(char));
        text[pocetZnaku] = '\0';
    }
    return text;
}

int vstupCislaVIntervalu() {
    int c, z, navrat;
    do {
        printf("Zadejte cislo v intervalu %d a %d ktere urci o kolik se kotouc pootoci.\n", MIN, MAX);
        scanf("%d", &c);
        z = 0;
        while (getchar() != '\n') {
            z++;
        }
        if (z != 0 || c < MIN || c > MAX) {
            printf("Spatny format zapisu. Zadej znovu. \n");
        }
    } while (z != 0 || c < MIN || c > MAX);
    return c;
}


void sifrovacka(char *text, int posun) {
    int d = strlen(text);
    for (int i = 0; i < d; i++) {
        if (isalpha(text[i])) {
            if (islower(text[i]) ? text[i] + posun > 'z' : text[i] + posun > 'Z') {
                text[i] -= MAX;
            }
            text[i] += posun;
        }
    }
}

void desifrovacka(char *text, int posun) {
    int d = strlen(text);
    for (int i = 0; i < d; i++) {
        if (isalpha(text[i])) {
            if (islower(text[i]) ? text[i] - posun < 'a' : text[i] - posun < 'A') {
                text[i] += MAX;
            }
            text[i] -= posun;
        }
    }
}

int main(void) {
    char *textProSifru = NULL;
    textProSifru = vstup(textProSifru);
    printf("Zadal jste text %s \n", textProSifru);
    int posun;
    posun = vstupCislaVIntervalu();
    printf("Zadal jste cislo %d \n", posun);
    int mod = 0;
    printf("Chcete desifrovat? (1/0) \n");
    scanf("%d", &mod);
    if (mod == 1) {
        desifrovacka(textProSifru, posun);
        printf("Desifrovany text: %s \n", textProSifru);
    } else {
        sifrovacka(textProSifru, posun);
        printf("Zasifrovany text: %s \n", textProSifru);
    }
    return 0;
}
