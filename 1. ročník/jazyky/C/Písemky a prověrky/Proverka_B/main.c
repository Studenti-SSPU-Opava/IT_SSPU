#include <stdio.h>  // Include the standard input/output library

#define CISLA "cisla.txt"  // Define the file name for the input file
#define VYSTUP "vystup.txt" // Define the file name for the output file

typedef struct { // Define a structure for the numbers
    int zaklad;
    int exponent;
    int mocnina;
} CISLO;

void hlavickaProgram(){ // create a function for the header for the program in the terminal
    printf("Vypis cisel ze souboru %s\n", CISLA);
    printf("--------------------------------\n");
    printf("poradi  zaklad  exponent  mocnina\n");
}

void hlavickaVystup(FILE *vystup){ // create a function for the header for the output file
    fprintf(vystup, "Vypis cisel s prvociselnym zakladem ze souboru %s\n", CISLA);
    fprintf(vystup, "--------------------------------------------------------\n");
}

int prvocislo(int cislo){ // create a function to check if the number is a prime number
    if (cislo < 2) {
        return 0;
    }
    for (int i = 2; i < cislo; i++) {
        if (cislo % i == 0) {
            return 0;
        }
    }
    return 1;
}

int mocnina(int zaklad, int exponent){ // create a function to calculate the power of a number
    int vysledek = 1;
    for (int i = 0; i < exponent; i++) {
        vysledek *= zaklad;
    }
    return vysledek;
}

int main(){
    FILE *cisla;
    FILE *vystup;
    CISLO cislo;
    int poradi = 0;
    int poradiVystup = 0;

    if ((cisla = fopen(CISLA, "r")) == NULL) { // open the input file
        printf("File %s has had an error opening.\n", CISLA);
    } else { 
        if ((vystup = fopen(VYSTUP, "w")) == NULL) { // open the output file
            printf("File %s has had an error opening.\n", VYSTUP);
        }
        hlavickaProgram(); // write the header to the terminal
        hlavickaVystup(vystup); // write the header to the output file
        while (fscanf(cisla, "%5d%5d", &cislo.zaklad, &cislo.exponent) == 2) { // read the numbers from the input file
            poradi++;
            // write the numbers to the terminal
            printf("%5d.   %5d     %5d    %5d\n", poradi, cislo.zaklad, cislo.exponent, mocnina(cislo.zaklad, cislo.exponent));
            if (prvocislo(cislo.zaklad) == 1) { // check if the number is a prime number
                poradiVystup++;
                // write the numbers to the output file
                fprintf(vystup, "%5d.  %5d   %5d    %5d\n", poradiVystup, cislo.zaklad, cislo.exponent, mocnina(cislo.zaklad, cislo.exponent)); 
            }
        }
        fprintf(vystup, "The file %s contains %d pairs of numbers.\n", VYSTUP, poradiVystup);

        if (fclose(cisla) == EOF) { // close the input file
            printf("The file %s has had an error closing.\n", CISLA);
        }
        if (fclose(vystup) == EOF) { // close the output file
            printf("The file %s has had an error closing.\n",VYSTUP);
        } else { 
            printf("The file %s has been created with pairs of numbers equal to %d.\n", VYSTUP, poradi);
        }
    }
    return 0;
}