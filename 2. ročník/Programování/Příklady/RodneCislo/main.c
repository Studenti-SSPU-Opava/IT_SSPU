#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int isLeapYear(int year) {
    return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
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

int input(const char* text){
    int input;
    int cc;

    do {
        printf("%s", text);
        scanf("%d", &input);

        cc = 0;
        
        while (getchar() != '\n') {
            cc++;
        }

        if (cc != 0) {
            printf("Neplatny vstup.\n");
        }
    } while (cc != 0);
    return input;
}

void generateRC() {
    int year, month, day, gender, endNum, controlNum;
    char rc[11];
    char checkRc[10];

    do{
        year = input("Zadej rok (1954-2053):\n");
        month = input("Zadej mesic (1-12):\n");
        day = input("Zadej den v (1-31):\n");
        gender = input("Zadej pohlaví (0 - zena, 1 - muz):\n");

        if (!isValidDate(day, month, year)) {
            printf("Neplatné datum.\n");
        } 
    } while (!isValidDate(day, month, year));

    if (gender == 0) {
        month += 50;
    } 

    do {
        endNum = rand() % 1000;
        sprintf(checkRc, "%02d%02d%02d%03d", year % 100, month, day, endNum);
        checkRc[9] = '\0';
    } while ((controlNum = atoi(checkRc)) % 11 == 10);

    sprintf(rc, "%s%d", checkRc, controlNum % 11);

    printf("Rodne cislo: %s\n", rc);
}

int main() {
    srand(time(NULL));
    int constantine;
    do{
        generateRC();
        constantine = input("Chcete pokracovat? (1-ano)\n");
    } while (constantine == 1);
    return 0;
}