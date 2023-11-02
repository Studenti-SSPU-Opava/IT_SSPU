#include <stdio.h>

#define PIN 1234
#define POCETPOKUSU 3

int main() {
    int pin;
    int countOfChar;
    int pokusy = POCETPOKUSU;
    do {
        printf("Zadej pin.\n");
        scanf("%d", &pin);
        countOfChar = 0;
        while (getchar() != '\n') {
            countOfChar++;
        }
        pokusy--;
        if (countOfChar != 0) {
            printf("Zadal jsi nespravny PIN.\n");
            pin = 0;
        }
        else if (pin == PIN) {
            printf("Zadal jsi spravny PIN.\n");
        }
        else {
            printf("Zadal jsi nespravny PIN.\n");
        }
    } while (pokusy > 0 && pin != PIN);
    return 0;
}