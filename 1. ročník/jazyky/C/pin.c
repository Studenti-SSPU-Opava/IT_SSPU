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
            printf("Zadal jsi nespravny pin.\n");
            pin = 0;
        } else if (pin == PIN) {
            printf("Zadal jsi spravny pin.\n");
        } else {
            printf("Zadal jsi nespravny pin.\n");
        }
        if (pin != PIN) {
            if (pokusy > 0) {
                printf("Zbyva%s jeste %d %s.\n",pokusy == 1 ? "":"ji", pokusy,pokusy == 1 ? "pokus":"pokusy");
            } else {
                printf("Nemas zadne pokusy.\n");
            }
        }
    } while (pokusy > 0 && pin != PIN);
    return 0;
}
