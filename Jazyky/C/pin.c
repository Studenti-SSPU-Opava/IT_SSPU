#include <stdio.h>

#define PIN 1234 //definuje konstantu PIN
#define POCETPOKUSU 3 //definuje konstantu POCETPOKUSU

int main() {
    int pin; //vytvoří proměnnou pin
    int countOfChar; //vytvoří proměnnou countOfChar
    int pokusy = POCETPOKUSU; //vytvoří proměnnou pokusy a nastaví její hodnotu na POCETPOKUSU
    do {
        printf("Zadej pin.\n"); //vypíše zprávu do konzele
        scanf("%d", &pin); //počká na zadání uživatele a uloží vstup do proměnné pin jako intager
        countOfChar = 0; //nastaví proměnnou countOfChar na 0
        while (getchar() != '\n') { //pokud je v I/O bufferu znak, maže po jednom znaku
            countOfChar++; //přičte k proměnné countOfChar 1
        }
        pokusy--; //odečte z proměnné pokusy 1
        if (countOfChar != 0) { //pokud countOfChar není 0
            printf("Zadal jsi nespravny PIN.\n"); //vypíše do konzole
            pin = 0; //nastaví proměnnou pin na 0
        }
        else if (pin == PIN) { //jinak pokud pin == PIN
            printf("Zadal jsi spravny PIN.\n"); //vypíše do konzole
        }
        else { //jinak
            printf("Zadal jsi nespravny PIN.\n"); //vypíše do konzole
        }
    } while (pokusy > 0 && pin != PIN); //opakuje pokud je proměnná pokusy > 0 a zárověň pin != PIN
    return 0;
}