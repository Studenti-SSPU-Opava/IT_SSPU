#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

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

int nejstarsiCyklista(DATA *data, int pocet) {
    int index = 0;
    for (int i = 1; i < pocet; i++) {
        if (data[i].rocnik < data[index].rocnik) {
            index = i;
        }
    }
    return index;
}

int nejmladsiCyklista(DATA *data, int pocet) {
    int index = 0;
    for (int i = 1; i < pocet; i++) {
        if (data[i].rocnik > data[index].rocnik) {
            index = i;
        }
    }
    return index;
}

int vek(int rocnik) {
    time_t t = time(NULL);
    struct tm *tim = localtime(&t);
    return (tim->tm_year + 1900) - rocnik;
}    

int prevodCasu(CAS *cas){
    return (cas->hod * 36000) + (cas->min * 600) + (int)cas->sec * 10;
}

void swap(DATA *a, DATA *b) {
    DATA temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(DATA *data, int pocet) {
    int i, j;
    int swapped;
    for (i = 0; i < pocet - 1; i++) {
        swapped = 0;
        for (j = 0; j < pocet - i - 1; j++) {
            if (prevodCasu(&data[j].cas) > prevodCasu(&data[j + 1].cas)) {
                swap(&data[j], &data[j + 1]);
                swapped = 1;
            }
        }
        if (swapped == 0) {
            break;
        }
    }
  
}

void vypis(DATA *data, int pocet) {
    int index = nejstarsiCyklista(data, pocet);
    int cz = 0;
    int sk = 0;
    for (int i = 0; i < pocet; i++) {
        printf("%d %15s %15s %3s %d %50s %02d:%02d:%04.1f\n", data[i].StartovniCislo, data[i].Prijmeni, data[i].Jmeno, data[i].narodnost, 
                                                                data[i].rocnik, data[i].klub, data[i].cas.hod, data[i].cas.min, data[i].cas.sec);
        if (strcmp(data[i].narodnost, "CZE") == 0) {
            cz++;
        } else if (strcmp(data[i].narodnost, "SVK") == 0) {
            sk++;
        }
    }
    printf("Pocet cyklistu: %d\n", pocet);
    printf("Nejstarsi cyklista je %s %s narozen v roce %d. Je mu %d let.\n", data[0].Prijmeni, data[0].Jmeno, data[0].rocnik, 2023 - data[0].rocnik);
    printf("Nejmladsi cyklista je %s %s narozen v roce %d. Je mu %d let.\n", data[pocet - 1].Prijmeni, data[pocet - 1].Jmeno, 
                                                                             data[pocet - 1].rocnik, 2023 - data[pocet - 1].rocnik);
    printf("Pocet cyklistu z CR: %d\n", cz);
    printf("Pocet cyklistu ze SVK: %d\n", sk);
}

int main(void) {
    DATA *data;
    int pocet = 0;
    data = cteni(&pocet);
    bubbleSort(data, pocet);
    vypis(data, pocet);
    return 0;
} 