#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Funkce pro zjisteni, zda je rok prestupny
int isLeapYear(int year) {
    return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
}

// Funkce pro kontrolu platnosti dat
int checkDay(int day, int month, int year) {
    if (day < 1 || day > 31) {
        return 0;
    } 

    if (month == 2) {
        if (isLeapYear(year)) {
            return 29;
        } else {
            return 28;
        }
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    } else {
        return 31;
    }
}

// Funkce pro vstup uzivatele
int input(const char* text) {
    int input;
    int charCount;

    do {
        printf("%s", text);
        scanf("%d", &input);

        charCount = 0;
        
        while (getchar() != '\n') {// Kontrola bufferu
            charCount++;
        }

        if (charCount != 0) {
            printf("Neplatny vstup.\n");
        }
    } while (charCount != 0);
    return input;
}

// Funkce pro seskladani a generovani rodneho cisla
void genRc() {
    int year, month, day, gender, endNum, controlNum;
    char checkRc[10];

    do {
        year = input("Zadej rok (1954-2053):\n");
        if (year < 1954 || year > 2053) {
            printf("Neplatny rok.\n");
        }
    } while (year < 1954 || year > 2053);
    do {
        month = input("Zadej mesic (1-12):\n");
        if (month < 1 || month > 12) {
            printf("Neplatny mesic.\n");
        }
    } while (month < 1 || month > 12);

    int maxDay = checkDay(1, month, year);
    char dayPrompt[20];
    sprintf(dayPrompt, "Zadej den (1-%d):\n", maxDay);

    do {
        day = input(dayPrompt);
        if (!checkDay(day, month, year)) {
            printf("Neplatny den.\n");
        }
    } while (!checkDay(day, month, year));

    do {
        endNum = input("Zadej posledni tri cislice rodneho cisla (000-999):\n");
        if (endNum < 0 || endNum > 999) {
            printf("Neplatne cislo.\n");
        }
    } while (endNum < 0 || endNum > 999);

    gender = input("Zadej pohlaví (0 - zena, 1 - muz):\n");

    if (gender == 0) {
        month += 50;
    } 

    do {
        sprintf(checkRc, "%02d%02d%02d%03d", year % 100, month, day, endNum);
        checkRc[9] = '\0';
    } while ((controlNum = atoi(checkRc)) % 11 == 10);

    printf("Rodne cislo: %02d%02d%02d/%03d%01d\n", year % 100, month, day, endNum, controlNum % 11);
}

int main() {
    srand(time(NULL)); // Inicializace generatoru nahodnych cisel
    int constantine;

    do {
        genRc();
        constantine = input("Chcete pokracovat? (1-ano)\n");
    } while (constantine == 1);

    return 0;
}