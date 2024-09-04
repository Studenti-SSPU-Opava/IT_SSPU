#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10

int main() {
    //spusteni generatoru nahodnych cisel
    srand((unsigned) time(NULL));
    int nahodne;
    int pocetPokusu;
    int countOfChar;
    int cislo;
    nahodne = rand() % MAX + 1;
    pocetPokusu = 0;
    do {
        printf("Zadej cislo od 1 do %d\n", MAX);
        scanf("%d", &cislo);
        pocetPokusu++;
        countOfChar = 0;
        while (getchar() != '\n') {
            countOfChar++;
        }
        if (countOfChar != 0) {
            // do promenne cislo ulozime neplatnou hodnotu
            cislo = MAX + 1;
        } else if (cislo == nahodne) {
            printf("Uhodl jsi cislo. Pocet pokusu %d.\n", pocetPokusu);
        } else {
            printf("Neuhodl jsi, zadej znovu.\n");
        }
    } while (cislo != nahodne);
    return 0;
}
