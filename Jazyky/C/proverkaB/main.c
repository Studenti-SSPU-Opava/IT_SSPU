#include <stdio.h>

#define CISLA "cisla.txt"
#define VYSTUP "vystup.txt"

void hlavickaProgram(){
    printf("Vypis cisel ze souboru %s\n", CISLA);
    printf("----------------------------\n");
}

int main(){
    FILE *cisla;
    FILE *vystup;

    if ((cisla = fopen(CISLA, "r")) == NULL) {
        printf("File %s has had an error opening.\n", CISLA);
    } else {
        if ((vystup = fopen(VYSTUP, "w")) == NULL) {
            printf("File %s has had an error opening.\n", VYSTUP);
        }

    return 0;
}