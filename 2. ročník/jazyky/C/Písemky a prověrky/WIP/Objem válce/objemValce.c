/*
 * objemValce.c ver. 1.0
 *
 * Program který počítá objemy válců ze souboru
 * ============================================
 *
 * František Rubáček - 2. 10. 2024
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#define NAHRAT "cisla.txt"    // Název souboru pro otevření
#define ULOZIT "hladiny.txt"  // Název souboru pro uložení

typedef struct
{
    int polomer;        //
    int vyskaHladiny;   // uložení válců ze souboru
    int mnostviVody;    //
}VALEC;

typedef struct 
{
    FILE* otevrit;
    FILE* ulozit;
}SOUBORY;


SOUBORY otevriSoubor(){
    SOUBORY soubor;
    soubor.otevrit = fopen(NAHRAT, "r");
    if (soubor.otevrit == NULL)
    {
        printf("Soubor %s se nepodarilo otevrit, program se ukonci\n", NAHRAT);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Soubor %s byl otevren\n", NAHRAT);
    }
    
    soubor.ulozit = fopen(ULOZIT, "w");
    if (soubor.ulozit == NULL)
    {
        printf("Soubor %s se nepodarilo otevrit, program se ukonci\n", ULOZIT);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Soubor %s byl vytvoren\n", ULOZIT);
    }
    return soubor;
}
 
void zavriSoubor(SOUBORY soubor){
    fclose(soubor.otevrit);
    if (soubor.otevrit == EOF)
    {
        printf("Soubor %s se nepodarilo uzavrit\n", NAHRAT);
    }
    else
    {
        printf("Soubor %s byl uzavren\n", NAHRAT);
    }
    fclose(soubor.ulozit);
    if (soubor.ulozit == EOF)
    {
        printf("Soubor %s se nepodarilo uzavrit\n", ULOZIT);
    }
    else
    {
        printf("Soubor %s byl uzavren\n", ULOZIT);
    }
}

void vypocet(SOUBORY soubor){
    VALEC valec;
    vypisDoKonzole();
    vypisDoSouboru(soubor);
    while (fscanf(soubor.otevrit,"%d %d %d", &valec.polomer, &valec.vyskaHladiny, &valec.mnostviVody) == 3)
    {
        printf("%i %i %i\n", valec.polomer, valec.vyskaHladiny, valec.mnostviVody);
    }
    
}

void vypisDoKonzole(){
    printf("V A L C E\n");      //vypíše hlavičku do konzole
    printf("---------\n");
    printf("      polomer   vyska      objem valce     mnozstvi vody\n");
    printf("         (cm)    (cm)     (dm krychlove)         (litry)\n");
    printf("--------------------------------------------------------\n");
}

void vypisDoSouboru(SOUBORY soubor){
    fprintf(soubor.ulozit,"V A L C E   S   V Y H O V U J I C I M   O B J E M E M\n");  //vypíše hlavičku souboru
    fprintf(soubor.ulozit,"-----------------------------------------------------\n");
    fprintf(soubor.ulozit,"    polomer       vyska    objem valce     mnostvi vody    vyska hladiny\n");
    fprintf(soubor.ulozit,"       (cm)        (cm)   (dm krychlove)        (litry)             (cm)\n");
    fprintf(soubor.ulozit,"------------------------------------------------------------------------\n");
}

int main() {
    SOUBORY soubor = otevriSoubor();
    vypocet(soubor);
    zavriSoubor(soubor);
    return 0;
}