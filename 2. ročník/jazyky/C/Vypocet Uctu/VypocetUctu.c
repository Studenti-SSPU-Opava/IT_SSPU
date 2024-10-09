/*
 * VypocetUctu.c ver. 1.1
 *
 * Program na vypocet uctu s urokem 
 * za cely rok a vkladem kazdy mesic
 * =================================
 *
 * v1.0 - Elias Constantine - 25.9.2024 
 * v1.1 - František Rubáček - 9.10.2024 - upravil jsem köd pro výpis do souboru pro lepší čitelnost, spravený uživatelský vstup
 * 
 */

#include <stdio.h>
#define UROKOVAMIRA 5.61 // Úroková míra
#define MINVKLAD 100 // Minimální vklad
#define MAXVKLAD 100000 // Maximální vklad
#define VYPLATA 15 // 15. den v měsíci
#define ROK 2024 // Rok
#define SOUBOR "vypisUctu.txt" // Soubor

// Funkce pro kontrolu přestupného roku
int leapYear(){
    if (ROK % 4 == 0 && (ROK % 100 != 0 || ROK % 400 == 0)) {
        return 1;
    } else {
        return 0;
    }
}

// Funkce pro získání počtu dní v měsíci
int daysInMonth(int month){
    int array [] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (leapYear() == 1) {
        array[1] = 29;
    } else {
        array[1] = 28;
    } 
    return array[month-1];
}

// Funkce pro vstup uživatele
int input(int vstup) {
    int input, countOfChar;
    
    do {
        countOfChar = 0;
        switch (vstup)
        {
        case 1:
            printf("Zadejte stav na zacatku roku:\n");
            break;
        
        case 2:
            printf("Zadejte mesicni vklad:\n");
            break;

        default:
            printf("Chyba ve funkci input()\n");
            exit(EXIT_FAILURE);
        }
        
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

// Funkce pro zápis do souboru
void writeToFile(FILE *file, float input, float inputMonth) {
    for (int i = 1; i <= 12; i++) {
        fprintf(file, "%2d.%2d.%2d\n", daysInMonth(i), i, ROK);
        fprintf(file, "--------------------------------------\n");
        fprintf(file, "   Datum  | Stav uctu | Urok | Vklad\n");
        fprintf(file, "--------------------------------------\n");
        for (int j = 1; j <= daysInMonth(i); j++) { // Výpis dnů v měsíci
            fprintf(file, "%2d.%2d.%2d | %.2f | %.2f | %.2f\n", j, i, ROK, input, input * UROKOVAMIRA / 100 / 365, inputMonth);
            input += input * UROKOVAMIRA / 100 / 365;
            if (j == VYPLATA) {
                input += inputMonth;
            }
        }
        fprintf(file, "----------------------------------\n\n");
    }
}

// Funkce pro zápis hlavičky do souboru
int hlavicka(FILE *file) {
    float bigInput = input(1);
    fprintf(file, "Sporici ucet, rocni urokova mira %.2f %%\n"
                  "Stav uctu na zacatku roku %d je %.2f\n"
                  "-------------------------------------------\n\n", UROKOVAMIRA, ROK, bigInput);
    return bigInput;
}

// Funkce pro výpočet úroku
double vypocetUroku(double vklad, double urokovaMira, int pocetDni) {
    return vklad * urokovaMira / 100 / 12;
}

int main (){
    int mesic, den, plat;
    FILE *file = fopen(SOUBOR,"w"); 
    if (file == NULL) {
        printf("soubor %s se nepodarilo otevrit", SOUBOR);
        return 1;
    }
    float inputStart = input(2);
    int zacatekRoku = hlavicka(file);
    writeToFile(file, zacatekRoku, inputStart);

    fclose(file);
    if (file == NULL) {
        printf("soubor %s se nepodarilo zavrit", SOUBOR);
        return 1;
    } else {
        printf("Vypis uctu byl uspesne ulozen do souboru %s\n", SOUBOR);
    }
   
    return 0;
}