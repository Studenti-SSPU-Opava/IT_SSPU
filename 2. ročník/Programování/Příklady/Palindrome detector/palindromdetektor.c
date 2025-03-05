#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DELIM " ,.-!?;\":&/\\\'"

char* vstup(char* pointer){
    char outputChar;
    int pot = 0;
    printf("Zadejte vetu: ");
    while((outputChar = getchar()) != '\n'){
        pointer = (char *) realloc(pointer, sizeof(char) *(pot + 1));
        if (pointer == NULL){
            printf("Chyba alokace pameti");
            exit(1);
        } else {
            pointer[pot] = outputChar;
            pot++;
    }
}
    pointer = (char *) realloc(pointer, sizeof(char) *(pot + 1));
    pointer[pot] = '\0';
    return pointer;
}

int palindrom(const char* slovo){
    if (strlen(slovo)==1){
        return 0; 
    }
    for (int i = 0; i < strlen(slovo)/2; i++){
        if (isalpha(slovo[i]) || tolower(slovo[i]) != tolower(slovo[strlen(slovo) - 1 - i])){
            return 0;
        }
    }
    return 1;
}

int pokracovani(){
    char pokracovat;
    printf("Chcete pokracovat? (A/N): ");
    scanf("%c", &pokracovat);
    if (pokracovat == 'A' || pokracovat == 'a'){
        return 1;
    } else {
        return 0;
    }
}

int main(void){
    char* pointer = NULL;
    char* pch;
    int pandromy;
    do {
    pandromy = 0;    
    pointer = vstup(pointer);
    printf("%s\n\n", pointer);
    pch = strtok(pointer, DELIM);
    while (pch != NULL){
        if (palindrom(pch)){
            printf("%s\n", pch);
            pandromy++;
        }
        pch = strtok(NULL, DELIM);
    }
    if (pandromy == 0){
        printf("V textu nejsou zadne palindromy\n");
    } else {
        printf("Celkem bylo nalezeno %d palindromu\n", pandromy);
    }
    pokracovani();
    free(pointer);
    pointer = NULL;
    } while (pokracovani());
    return 0;
}