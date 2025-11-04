/*
 * kontrolaIntervaluCisla.c ver. 1.0
 * 
 * Zeptá se uživatele na vstup a zkontroluje zda
 * je v intervalu MIN - MAX
 * ========================================
 *
 * 2023
 * 
 */

#include <stdio.h>

#define MIN 1            // nastaví minimalní interval
#define MAX 100          // nastaví maximální interval

int main() {
    int zadaneCislo, countOfChar;
    do {
        printf("Zadej cislo intervalu od %d do %d:\n", MIN, MAX);
        scanf("%d", &zadaneCislo);
        countOfChar = 0;
        while (getchar() != '\n') {
            countOfChar++;
        }
        if (countOfChar != 0) {
            printf("Nezadal jsi spravne cislo, zadej ho znovu.\n");
        } else if (zadaneCislo < MIN || zadaneCislo > MAX) {
            printf("Nezadal jsi cislo v intervalu, zadej ho znovu.\n");
        }
    }while (countOfChar != 0 || zadaneCislo < MIN || zadaneCislo > MAX);
    printf("Cislo %d je v intervalu %d-%d.\n",zadaneCislo,MIN,MAX);
    return 0;
}
