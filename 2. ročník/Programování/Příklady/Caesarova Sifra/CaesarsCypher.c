#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 26

char *ziskaniVety(char *pointer){
    int i = 0;
    int znak;
    printf("Zadejte vetu k sifrovani: ");

    while ((znak = getchar()) != '\n') {

        pointer = (char *) realloc(pointer, (i + 1) * sizeof(char));
        
        if (pointer != NULL){
            pointer[i] = (char) znak;
            i++;
        }
        else{
            printf("Chyba alokace pameti");
            break;
        }
    }
    if (pointer != NULL){
        pointer = (char *)realloc(pointer, (i+1) * sizeof(char));
        if (pointer != NULL){
        pointer[i] = '\0';
        }
    }
    return pointer;
}

int vstupCisla(int min, int max) {
    int vystup;
    int charCount;

    do{
        printf("Zadejte o kolik se pismena posunou od %d - %d: ", min, max);

        
        scanf("%d", &vystup);
        charCount = 0;
        while (getchar() != '\n') {
            charCount++;
        }

        if (charCount != 0) {
            printf("Zadali jste nespravny vstup.\n");
        } else if (vystup < min || vystup > max) {
            printf("Zadali jste cislo mimo rozsah.\n");
        }
    } while (charCount != 0 || vystup < min || vystup > max);
    return vystup;
}

void sifrovani(char *pointer , int posun){
    for (int i = 0; i < strlen(pointer); i++){
        if (isalpha(pointer[i])){
            if (pointer[i] + posun > isupper(pointer[i]) ? 'Z' : 'z'){
                pointer[i] -= MAX;
            }
            pointer[i] += posun;
        }
    }
}

int main(void){
    char *pointer = NULL;
    int posun;
    pointer = ziskaniVety(pointer);
    posun = vstupCisla(0, MAX);
    printf("%s\n%d", pointer, posun);
    sifrovani(pointer, posun);
    printf("\n%s", pointer);
    free(pointer);

    return 0;
}