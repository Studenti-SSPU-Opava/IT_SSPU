#include <stdio.h>
#include <string.h>

int checkValChar(char str[]){
    size_t len = strlen(str);
    for (int i = 0; i < strlen(str); i++){
        if (
            (str[i] < '0' || str[i] > '9') 
            && str[i] != ' '
            && str[i] != '-'
            && str[i] != 'X'
            && str[i] != 'x'
            && (i == strlen(str) - 1 || ((str[i] == '-' || str[i] == ' ') && str[i] == str[i + 1]))
        ) {
            printf("ISBN obsahuje neplatné znaky.\n");
            return 0;
        }
    }
    for (int i = 0; i < strlen - 1; i++) {
        if (((str[i] == '-' || str[i] == ' ') && str[i] == str[i + 1])) {
            printf("ISBN obsahuje neplatné znaky.\n");
            return 0;
        }
    }
    return 1;
}

int checkValidity(char str[]){
    char string[20];
    char numStr[20];
    char *temp;
    int numberSum = 0;

    strcpy(string, str);
    temp = strtok(string, "- ");

    while (temp != NULL){
        strcat(numStr, temp);
        temp = strtok(NULL, "- ");
    }

    if (strlen(numStr) != 10 && strlen(numStr) != 13){
        printf("ISBN musí mít 10 číslic.\n");
        return 0;
    }

    if(strlen(numStr) == 10){
      for ( int i = 0; i < strlen(numStr); i++){
          numberSum += (numStr[i] - '0') * ((i + 1)%2 == 1 ? 1 : 3);
      }
    }
}

int input(char str[]){
    printf("Zadejte ISBN: ");
    fgets(str, 20, stdin);

    int index = strcspn(str, "\n");
    str[index] = '\0';

    checkValChar(str);
    checkValidity(str);
}

int main(void){
    char str[20];
    input(str);
    printf("%s", str);
  
   
    return 0;
}