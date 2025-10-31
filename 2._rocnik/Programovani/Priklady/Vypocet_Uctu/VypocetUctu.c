#include <stdio.h>
#define UROKOVAMIRA 5.61
#define MINVKLAD 100
#define MAXVKLAD 100000
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

void writeToFile(FILE *file, float input, float inputMonth) {
    for (int i = 1; i <= 12; i++) {
        fprintf(file, "%d.%2d.%d\n", daysInMonth(i), i, ROK);
        fprintf(file, "--------------------------------------\n");
        fprintf(file, "Datum     | Stav uctu | Urok | Vklad\n");
        fprintf(file, "--------------------------------------\n");
        for (int j = 1; j <= daysInMonth(i); j++) {
            fprintf(file, "%d.%d.%d | %.2f | %.2f | %.2f\n", j, i, ROK, input, input * UROKOVAMIRA / 100 / 365, inputMonth);
            input += input * UROKOVAMIRA / 100 / 365;
            if (j == DAN) {
                input += inputMonth;
            }
        }
        fprintf(file, "--------------------------------------\n");
    }
}

void hlavicka(FILE *file, float startInput) {
    float bigInput = input();
    fprintf(file, "Sporici ucet, rocni urokova mira %.2f %%\n"
            "Stav uctu na zacatku roku %d je %.2f\n"
            "--------------------------------------", UROKOVAMIRA, ROK, bigInput);
}

double vypocetUroku(double vklad, double urokovaMira, int pocetDni) {
    return vklad * urokovaMira / 100 / 12;
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
    writeToFile(file, inputStart, input());
   


    return 0;
}