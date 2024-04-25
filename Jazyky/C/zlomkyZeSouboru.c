#include <stdio.h>

#define INPUTFILE "zadani.txt"
typedef struct {
    int citatel;
    int jmenovatel;
} ZLOMEK;

int main() {
    FILE * fr;
    ZLOMEK z1, z2;
    fr = fopen(INPUTFILE, "r");
    if (fr == NULL) {
        printf("Soubor %s neexistuje nebo nejde otevrit.\n", INPUTFILE);
    } else {
        while (fscanf(fr,"%d %d %d %d", &z1.citatel, &z1.jmenovatel, &z2.citatel, &z2.jmenovatel) == 4)
        {
            printf("Zlomek 1: %d/%d Zlomek 2: %d/%d\n", z1.citatel, z1.jmenovatel, z2.citatel, z2.jmenovatel);
        }
        if (fclose(fr) == EOF) {
        printf("Soubor %s se nepodarilo uzavrit.\n", INPUTFILE);
    }
}
    
    return 0;
}