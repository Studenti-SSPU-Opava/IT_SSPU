#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VSTUP "cyklistika.txt"
#define VELIKOST 100
typedef struct {
    int hod;
    int min;
    float sec;
}CAS;

typedef struct {
    int StartovniCislo;
    char Prijmeni[20];
    char Jmeno[20];
    char narodnost[20];
    int rocnik;
    char klub[20];
    CAS cas;
}DATA;

DATA *cteni(int *pocet) {
    FILE *file;
    char myString[VELIKOST + 1];
    DATA *pamet = NULL;
    DATA *mpamet = NULL;
    int i = 0;
    int j = 0;
    
    file = fopen(VSTUP, "r");
    if (file == NULL) {
        printf("Chyba pri otvarani suboru %s\n", VSTUP);
        return 0;
    }

    fgets(myString, VELIKOST, file);
    
    while (fgets(myString, VELIKOST, file) != NULL) {
        mpamet = (DATA *) realloc(pamet, sizeof(DATA) * (i + 1));

        if(mpamet != NULL) {
            pamet = mpamet;
            char *textCast;
            textCast = strtok(myString, ":;");
            j = 0;
            while (textCast != NULL) {
                switch (j)
                {
                case 0:
                    pamet[i].StartovniCislo = atoi(textCast);
                    break;
                case 1:
                    strcpy(pamet[i].Prijmeni, textCast);
                    break;
                case 2:
                    strcpy(pamet[i].Jmeno, textCast);
                    break;    
                case 3:
                    strcpy(pamet[i].narodnost, textCast);
                    break;
                case 4:
                    pamet[i].rocnik = atoi(textCast);
                    break;
                case 5:
                    strcpy(pamet[i].klub, textCast);
                    break;
                case 6:
                    pamet[i].cas.hod = atoi(textCast);
                    break;
                case 7:
                    pamet[i].cas.min = atoi(textCast);
                    break;
                case 8:
                    pamet[i].cas.sec = atof(textCast);
                    break;        
                }
                textCast = strtok(NULL, ":;");
                j++;
            }
        } else {
            free(pamet);
            printf("Chyba pri alokaci pameti.\n");
            return 0;
        }
        i++;
    }
    fclose(file);
    *pocet = i;
    return pamet;
}

void vypis(DATA *data, int pocet) {
    for (int i = 0; i < pocet; i++) {
        printf("%4d %10s %10s %3s %4d %30s %02d:%02d:%04.1f\n", data[i].StartovniCislo, data[i].Prijmeni, data[i].Jmeno, data[i].narodnost, 
                                                 data[i].rocnik, data[i].klub, data[i].cas.hod, data[i].cas.min, data[i].cas.sec);
    }
}

int main(void) {
    DATA *data;
    int pocet = 0;
    data = cteni(&pocet);
    vypis(data, pocet);

    if (data == NULL) {
        printf("Chyba pri alokaci pameti.\n");
        return 0;
    }
    
    free(data);
    return 0;
} 