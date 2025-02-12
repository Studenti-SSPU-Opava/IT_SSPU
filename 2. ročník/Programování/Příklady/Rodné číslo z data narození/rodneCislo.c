#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int isLeapYear(int year) {
    if (year % 4 != 0) return 0;
    if (year % 100 != 0) return 1;
    return (year % 400 == 0);
}

int isValidDate(int day, int month, int year) {
    if (year < 1954 || year > 2053) return 0;
    if (month < 1 || month > 12) return 0;
    if (day < 1 || day > 31) return 0;

    if (month == 2) {
        if (isLeapYear(year)) return day <= 29;
        else return day <= 28;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) return day <= 30;
    return 1;
}

void generateRC() {
    int year, month, day, gender, suffix;
    char rc[11];
    char input[10];

    printf("Zadej rok v intervalu 1954 a 2053:\n");
    scanf("%d", &year);
    printf("Zadej mesic v intervalu 1 a 12:\n");
    scanf("%d", &month);
    printf("Zadej den v intervalu 1 a 31:\n");
    scanf("%d", &day);
    printf("Zadej pohlaví (0 - zena, 1 - muz) v intervalu 0 a 1:\n");
    scanf("%d", &gender);
    printf("Zadej trojčíslí za lomítkem v intervalu 0 a 999:\n");
    scanf("%d", &suffix);

    if (!isValidDate(day, month, year)) {
        printf("Neplatné datum.\n");
        return;
    }

    if (gender == 0) {
        month += 60;
    }

    sprintf(rc, "%02d%02d%02d%03d", year % 100, month, day, suffix);

    int sum = 0;
    for (int i = 0; i < 9; i++) {
        sum += (rc[i] - '0') * (i < 6 ? (i % 2 == 0 ? 1 : 2) : (i % 2 == 0 ? 7 : 8));
    }

    int remainder = sum % 11;
    if (remainder == 10) {
        do {
            suffix = rand() % 1000;
            sprintf(rc, "%02d%02d%02d%03d", year % 100, month, day, suffix);
            sum = 0;
            for (int i = 0; i < 9; i++) {
                sum += (rc[i] - '0') * (i < 6 ? (i % 2 == 0 ? 1 : 2) : (i % 2 == 0 ? 7 : 8));
            }
            remainder = sum % 11;
        } while (remainder == 10);
    }

    rc[9] = (remainder == 10 ? '0' : '0' + remainder);
    rc[10] = '\0';

    printf("Bylo vytvoreno validní rodné číslo: %s\n", rc);
}

int main() {
    char input[10];
    srand(time(0));

    do {
        generateRC();
        printf("Pro opakovane zadani rodneho cisla stiskni Enter, pro ukonceni zadej 'k':\n");
        getchar(); // To consume the newline character left by scanf
        fgets(input, sizeof(input), stdin);
    } while (input[0] != 'k' && input[0] != 'K');

    return 0;
}