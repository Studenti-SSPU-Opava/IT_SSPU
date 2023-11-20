#include <stdio.h>

#define MIN 1
#define MAX 24*3600

int main() {
    int sekundy;
    int countOfChar;
    do {
        printf("Zadej pocet sekund v intervalu %d - %d:\n", MIN, MAX);
        countOfChar = 0;
        scanf("%d", &sekundy);
        while (getchar() != '\n') {
            countOfChar++;
        }
        if (countOfChar != 0) {
            printf("Nezadal jsi cele cislo. Zadej znovu.\n");
        } else if (sekundy < MIN || sekundy > MAX) {
            printf("Sekundy %d jsou mimo interval.\n", sekundy);
        }
    } while (countOfChar != 0 || sekundy < MIN || sekundy > MAX);
    printf("Cas %02d:%02d:%02d\n", sekundy / 3600, (sekundy - sekundy / 3600 * 3600) / 60, sekundy % 60);
    return 0;
}
