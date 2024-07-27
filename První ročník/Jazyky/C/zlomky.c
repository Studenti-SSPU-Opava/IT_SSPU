#include <stdio.h>

int vstup(const char *text, int *ktery){
    
    int bufferCount = 0;
    int cislo;
    do {
        if (bufferCount != 0) {
            printf("CHYBA: %s nebyly zadany jako cele cislo. Zadej znovu.\n", text);
        }
        printf("Zadej %s %d. zlomku\n", text, ktery);
        scanf("%d", &cislo);
        bufferCount = 0;
        while (getchar() != '\n') {
            bufferCount++;
        }
    } while (bufferCount != 0);
    return cislo;
}

int zlomkyDotaz(){
    int operace;
    int bufferCount;
    do {
        if (bufferCount != 0) {
            printf("CHYBA: Zadali jste spatnou operaci. Zadejte znovu.\n");
        }
        printf("Jakou operaci chcete provest?\n");
        printf("1 - scitani\n");
        printf("2 - odcitani\n");
        printf("3 - nasobeni\n");
        printf("4 - deleni\n");
        scanf("%d", &operace);
        bufferCount = 0;
        while (getchar() != '\n') {
            bufferCount++;
        }
    } while (bufferCount != 0 || operace < 1 || operace > 4);
    return operace;
}

int vypocet(int prvniZlomekCitatel, int prvniZlomekJmenovatel, int druhyZlomekCitatel, int druhyZlomekJmenovatel, int operace){
    int vysledekCitatel;
    int vysledekJmenovatel;
    switch (operace) {

int main() {
    int prvniZlomekCitatel = vstup("citatele", 1);
    int prvniZlomekJmenovatel = vstup("jmenovatele", 1);
    int druhyZlomekCitatel = vstup("citatele", 2);
    int druhyZlomekJmenovatel = vstup("jmenovatele", 2);
    printf("%d, %d, %d, %d", prvniZlomekCitatel, prvniZlomekJmenovatel, druhyZlomekCitatel, druhyZlomekJmenovatel);
    int operace = zlomkyDotaz();

    return 0;
}
