#include <stdio.h>
#define POCETPRVKU 256
#define POCETSLOUPCU 8
#define ZACATEK 14

int main() {
    for (int i = 0; i < POCETPRVKU; ++i) {
        printf("%4d %c",i,i);
    }
    return 0;
}