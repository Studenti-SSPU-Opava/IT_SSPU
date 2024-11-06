/*
*
* Elias Constantine v1.0 , 6.11.2024
*
*
*
*
*
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void numGeneration() { // Funkce pro Generovani nahodnych cisel
    int randomNums[50]; // Pole pro ulozeni nahodnych cisel
    srand(time(0)); // Inicializace generatoru nahodnych cisel

    for (int i = 0; i < 50; i++) { // Tady Generuje 50 nahodnych cisel
        randomNums[i] = rand() % 100;
    }

    printf("Vypis generovanych cisel\n" // Hlavicka
           "------------------------\n");

    for (int i = 0; i < 50; i++) {  // Tady vypisuje nahodna cisla do konzole
        printf("%2d ", randomNums[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }
}

void checkDuplicates() { // Funkce pro kontrolu opakujici se cisla
    int randomNums[50];
    int count[100] = {0}; // Pole pro ulozeni poctu vyskytu jednotlivych cisel
    srand(time(0)); 

    for (int i = 0; i < 50; i++) { // Tady zase generuje 50 nahodnych cisel
        randomNums[i] = rand() % 100; // Ulozi nahodne cislo do pole
        count[randomNums[i]]++; // Zvysi pocet vyskytu daneho cisla
    }

    printf("\nVicenasobne se vyskytujici cisla\n" // Hlavicka
           "--------------------------\n");
    for (int i = 0; i < 100; i++) { // Tady kontroluje, ktera cisla se vyskytuji vice nez jednou
        if (count[i] > 1) {
            printf("%d %d krat\n", i, count[i]);
        }
    }
}

int main() { // Hlavni funkce
    numGeneration(); 
    checkDuplicates();
    return 0;
}