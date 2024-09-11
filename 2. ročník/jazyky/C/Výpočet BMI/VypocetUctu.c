#include <stdio.h>
#define UROKOVAMIRA 5.61
#define MINVKLAD 1000
#define MAXVKLAD 10000
#define DAN 15
#define ROK 2024
#define SOUBOR "vypisUctu.txt"


int leapYear(){
    if (ROK % 4 == 0 && (ROK % 100 != 0 || ROK % 400 == 0)) {
        return 1;
    } else {
        return 0;
    }
}


int daysInMonth(int month){
    int array [] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (leapYear() == 1) {
        array[1] = 29;
    } else {
        array[1] = 28;
    } 
    return array[month-1];
}


int input() {
    int input, countOfChar;
    
    do {
        countOfChar = 0;
        printf("Zadejte mesicni plat:\n");
        printf("(Minimum %d maximum %d)\n", MINVKLAD, MAXVKLAD);
        scanf("%d", &input);
        while (getchar() != '\n') {
            countOfChar++;
        }
        if (countOfChar != 0) {
            printf("Zadali jste spatny vstup\n");
        } else if (input < MINVKLAD || input > MAXVKLAD) {
            printf("Zadali jste spatne cislo\n");
        } else {
            printf("Castka Prijata.\n");
        }
    } while (countOfChar != 0 || input < MINVKLAD || input > MAXVKLAD);
    return input;
}

void writeToFile(FILE *file, int den, int mesic, int rok, int plat) {
    fprintf(file, "%d.%d.%d %d\n", den, mesic, rok, plat);
}

void hlavicka(FILE *file, float startInput) {
    float bigInput = input();
    printf("Sporici ucet, rocni urokova mira %.2f %%\n"
            "Stav uctu na zacatku roku %d je %.2d\n"
            "--------------------------------------", UROKOVAMIRA, ROK, bigInput);
}



int main (){
    int mesic, den, plat;
    FILE *file = fopen(SOUBOR, "w"); 
    if (file == NULL) {
        printf("soubor %s se nepodarilo otevrit", SOUBOR);
        return 1;
    }
    float inputStart = input();
    hlavicka(file, inputStart);
    writeToFile(file, 1, 1, ROK, inputStart);
   


    return 0;
}