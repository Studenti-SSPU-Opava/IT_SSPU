#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define ISBN_10 10
#define ISBN_13 13
#define SIZE 20
#define ODDELOVACE " -"

// 1. Zadejte ISBN
void sbiraniISBN(char *pole) {
    printf("Zadej ISBN.\n");
    fgets(pole, SIZE, stdin);
    pole[strlen(pole) - 1] = '\0';
}


char isbnBezOdd(const char *pole, char *poleBezOd) {
    char *pch;
    char kopie[SIZE];
    strcpy(kopie, pole);
    strcpy(poleBezOd, ""); // vyprazdneni pole, ktere budeme plnit
    pch = strtok(kopie, ODDELOVACE);
    while (pch != NULL) {
        strcat(poleBezOd, pch);
        pch = strtok(NULL, ODDELOVACE);
    }
    return poleBezOd;
}

int kontrolaPlatnychZnaku(char *pole) {
    // kontrola platnych znaku
    for (int i = 0; i < strlen(pole); i++) {
        // if (!((pole[i] >= '0' && pole[i] <= '9') || pole[i] == ' ' || pole[i] == '-' || toupper(pole[i]) == 'X' )) {
        if ((pole[i] < '0' || pole[i] > '9') && pole[i] != ' ' && pole[i] != '-' && toupper(pole[i]) != 'X') {
            return 0;
        }
    }
    return 1;
}

int kontrolaOddelovacu(char *pole, char oddelovac) {
    int pocet = 0;
    for (int i = 0; i < strlen(pole) - 1; i++) {
        if (pole[i] == oddelovac && pole[i] == pole[i + 1]) {
            return 0;
        }
        if (pole[i] == oddelovac) {
            pocet++;
        }
    }
    if (pocet < 3 || pocet > 4) {
        return 0;
    }
    return 1;
}

int validaceISBN(char *pole, int typ) {
    int soucet = 0;
    if (typ == ISBN_10) {
        for (int i = 0; i < ISBN_10; i++) {
            if (pole[i] == 'X' && i == 9) {
                soucet += 10 * (i + 1);
            } else {
                soucet += (pole[i] - '0') * (i + 1);
            }
        }
        if (soucet % 11 == 0) {
            printf("ISBN-10 je platne.\n");
        } else {
            printf("ISBN-10 neni platne.\n");
        }
    } else if (typ == ISBN_13) {
        for (int i = 0; i < ISBN_13; i++) {
            if (i % 2 == 0) {
                soucet += pole[i] - '0';
            } else {
                soucet += (pole[i] - '0') * 3;
            }
        }
        if (soucet % 10 == 0) {
            printf("ISBN-13 je platne.\n");
        } else {
            printf("ISBN-13 neni platne.\n");
        }
    }
    return 1;
}

int typISBN(char *pole) {
    int delka = strlen(pole);
    if (delka == ISBN_10) {
        printf("Jedna se o ISBN-10.\n");
        validaceISBN(pole, ISBN_10);
    } else if (delka == ISBN_13) {
        printf("Jedna se o ISBN-13.\n");
        validaceISBN(pole, ISBN_13);
    } else {
        printf("Nejedna se o platne ISBN.\n");
        return 0;
    }
    return 1;
}

int kontrolaISBN(char *pole) {
    
    // kontrola platnych znaku
    char isbnBezOd[SIZE];
    if (!kontrolaPlatnychZnaku(pole)) {
        return 0;
    } else if (!kontrolaOddelovacu(pole, ' ') && !kontrolaOddelovacu(pole, '-')) {
        return 0;
    }
    isbnBezOdd(pole, isbnBezOd);
    printf("ISBN bez oddelovacu: %s.\n", isbnBezOd);
    typISBN(isbnBezOd);
    return 1;
}

int main(void) {
    int opakovani = 0;
    do{
        char isbn[SIZE];
        sbiraniISBN(isbn);
        if (kontrolaISBN(isbn)) {
            printf("Zadal jsi spravne ISBN: %s.\n", isbn);
        } else {
            printf("Chybne ISBN.\n");
        }
        do {
        opakovani = 0;
        printf("Chcete opakovat zadani? (1 - ano, 0 - ne)\n");
        scanf("%d", &opakovani);
        while (getchar() != '\n'); // Vyprázdnění vstupního bufferu
        } while (opakovani != 0 && opakovani != 1);
    } while (opakovani == 1);
    return 0;
}
