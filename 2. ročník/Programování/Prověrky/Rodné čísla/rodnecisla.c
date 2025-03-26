#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define DELKARC 10

enum { zena, muz }; //system konstant misto define s hodnotami {0, 1}

int rokNarozeni(const char *rodneCislo) {
    char rok[3];
    strncpy(rok, rodneCislo, 2);
    rok[2] = '\0';
    return atoi(rok) >= 54 ? atoi(rok) + 1900 : atoi(rok) + 2000;
}

int mesicNarozeni(const char *rodneCislo) {
    char mesic[3];
    strncpy(mesic, rodneCislo + 2, 2);
    mesic[2] = '\0';
    return atoi(mesic) > 50 ? atoi(mesic) - 50 : atoi(mesic);
}

int denNarozeni(const char *rodneCislo) {
    char den[3];
    strncpy(den, rodneCislo + 4, 2);
    den[2] = '\0';
    return atoi(den);
}

int vek(const char *rodneCislo) {
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    int systemovyRok = timeinfo->tm_year + 1900;
    int systemovyMesic = timeinfo->tm_mon + 1;
    int systemovyDen = timeinfo->tm_mday;
    int vek = systemovyRok - rokNarozeni(rodneCislo);
    if (systemovyMesic < mesicNarozeni(rodneCislo) || (systemovyMesic == mesicNarozeni(rodneCislo)
                                                       && systemovyDen < denNarozeni(rodneCislo))) {
        vek--;
    }
    return vek;
}

int pohlavi(const char *rodneCislo) {
    char mesic[3];
    strncpy(mesic, rodneCislo + 2, 2);
    mesic[2] = '\0';
    return atoi(mesic) > 50 ? zena : muz;
}

int kontrolaVstupu(const char *rodneCislo) {
    int zbytek;
    char prvni9Znaky[DELKARC];
    if (strlen(rodneCislo) != DELKARC) {
        return 0;
    }
    for (int i = 0; i < DELKARC; i++) {
        if (rodneCislo[i] < '0' || rodneCislo[i] > '9') {
            return 0;
        }
    }
    // Zkopirujeme prvnich 9 znaku z retezce rodneCislo.
    strncpy(prvni9Znaky, rodneCislo, 9); // Kvuli referenci nakonec pridame radeji binarni nulu.
    prvni9Znaky[9] = '\0';
    zbytek = atoi(prvni9Znaky) % 11;
    if (zbytek == rodneCislo[9] - '0') {
        // '0' je znakova nula, hodnota 48
        return 1;
    } else if (zbytek == 10 && rodneCislo[9] == '0') {
        return 1;
    } else {
        return 0;
    }
}

int ukonceni() {
    int cislo;
    int countOfChar;
    do {
        countOfChar = 0;
        printf("Zadej 0 pro ukonceni programu.\n");
        scanf("%d", &cislo);
        while (getchar() != '\n') {
            countOfChar++;
        }
        if (countOfChar != 0) {
            printf("Nezadal jsi cele cislo, zadej znovu.");
        }
    } while (countOfChar != 0);
    return cislo;
}

int main(void) {
    char rodneCislo[DELKARC + 1]; //kvuli binarni nuly + 1
    do {
        printf("Zadej rodne cislo o velikosti %d: \n", DELKARC);
        scanf("%s", rodneCislo);
        if (!kontrolaVstupu(rodneCislo)) {
            printf("Chybne rodne cislo. \n");
        } else {
            printf("Narodil ses %d. %d. %d\n",
                   denNarozeni(rodneCislo), mesicNarozeni(rodneCislo), rokNarozeni(rodneCislo));
            printf("Mas %d let.\n", vek(rodneCislo));
            printf("Tvoje pohlavi je %s.\n", pohlavi(rodneCislo) ? "muz" : "zena");
        }
    } while (ukonceni());
    return 0;
}
