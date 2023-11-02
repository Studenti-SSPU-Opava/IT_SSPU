#include <stdio.h>

#define PIN 1234
#define POCETPOKUSU 3

int main() {
    int pin;
    int     countOfChar;
    int pokusy = POCETPOKUSU;
    printf("Zadej pin.\n");
    scanf("%d", &pin);
    countOfChar = 0;
    while(getchar() != '\n') {
        countOfChar++;
    }
    pokusy--;
    if(countOfChar != 0) {
        printf("Zadal jsi nespravny PIN.\n");
    }
    else if()
    return 0;
}