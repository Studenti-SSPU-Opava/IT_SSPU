#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define _USE_MATH_DEFINES
#define INPUTFILE "cisla.txt"
#define OUTPUTFILE "hladiny.txt"
typedef struct {
    int polomer;
    int vyska;
    int litry;  //struktura která má na starost vstupní hodnoty ze vstupního souboru
} VALEC;

float objemValce(int polomer, int vyska) {
    float objem = (M_PI * (polomer * polomer) * vyska) /1000;  //výpočet objemu válce
    return objem;
}

float hladinaVody(int litry, int polomer){
    float vyska = (litry * 1000.0) / (M_PI * (polomer*polomer));  //výpočet výšky hladiny vody
    return vyska;
}

int main() {
    FILE * fr;  
    FILE * wr;
    VALEC v1;
    fr = fopen(INPUTFILE, "r");
    wr = fopen(OUTPUTFILE, "w");
    if (wr == NULL) {
        printf("Soubor %s nejde vytvorit nebo otevrit.\n", OUTPUTFILE);  //chybová hláška pokud nejde otevřít nebo vyvtořit výstupní soubor
        return 0;
    }
    fprintf(wr,"V A L C E   S   V Y H O V U J I C I M   O B J E M E M\n");  //vypíše hlavičku souboru
    fprintf(wr,"-----------------------------------------------------\n");
    fprintf(wr,"    polomer       vyska    objem valce     mnostvi vody    vyska hladiny\n");
    fprintf(wr,"       (cm)        (cm)   (dm krychlove)        (litry)             (cm)\n");
    fprintf(wr,"------------------------------------------------------------------------\n");
    if (fr == NULL) {
        printf("Soubor %s neexistuje nebo nejde otevrit.\n", INPUTFILE);  //chybová hláška pokud nejde otevřít vstupní soubor
    } else {
        int poradiKonzole = 0;
        int poradiSoubor = 0;
        printf("V A L C E\n");      //vypíše hlavičku do konzole
        printf("---------\n");
        printf("      polomer   vyska      objem valce     mnozstvi vody\n");
        printf("         (cm)    (cm)     (dm krychlove)         (litry)\n");
        printf("--------------------------------------------------------\n");
        while (fscanf(fr,"%d %d %d", &v1.polomer, &v1.vyska, &v1.litry) == 3)
        {
            poradiKonzole++;
            float objem = objemValce(v1.polomer, v1.vyska); 
            float vyska = hladinaVody(v1.litry, v1.polomer);
            printf("%3d.%5d cm%6d cm%11.2f dm%10d l\n",poradiKonzole, v1.polomer, v1.vyska, objem, v1.litry);   //vypíše hodnoty z prvního řádku souboru + výpočty do konzole
            if (vyska<=(float)v1.vyska){  //pokud se do válce vejde dané množství vody, vypíše paramtery tohoto válce do souboru
                poradiSoubor++;
                fprintf(wr, "%3d. %5d cm %6d cm %11.2f dm %14d l %13.2f cm \n",poradiSoubor, v1.polomer, v1.vyska, objem, v1.litry, vyska);
            }
        }
        fprintf(wr,"------------------------------------------------------------------------\n"); //vypíše patičku souboru
        printf("--------------------------------------------------------\n");  //vypíše patičku do konzole
        printf("Soubor "OUTPUTFILE" byl vytvoren.\n");
        if (fclose(fr) == EOF) {
        printf("Soubor %s se nepodarilo uzavrit.\n", INPUTFILE);  //chybová hláška pokud nejde zavřít vstupní soubor
        }
        if (fclose(wr) == EOF) {
        printf("Soubor %s se nepodarilo uzavrit.\n", OUTPUTFILE);  //chybová hláška pokud nejde zavřít výstupní soubor
    }
}
    return 0;
}