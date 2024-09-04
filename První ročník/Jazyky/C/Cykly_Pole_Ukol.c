//ukol z programovani 104

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 200
#define CHAR ('Z' - 'A' + 1)

/* int pole[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
                'P','Q','R','S','T','U','V','W','X','Y','Z'};
 */
char randompole[MAX + 1];

int main(){
    srand(time(NULL));
    int random;
    for(int i = 0; i < MAX; i++){
        random = rand() % (CHAR) + 'A'; //rand() % (max - min + 1) + min
        //random = rand() % 26;
        //randompole[i] = pole[random];
        randompole[i] = random;
    }
    randompole[MAX] = '\0'; //ukonceni retezce
/* 
    for(int i = 0; i < MAX; i++){
        printf("%c ", randompole[i]);
    } */
    printf("%s\n", randompole);

    int count[CHAR];
    /*for(int i = 0; i < MAX; i++){
        for(int j = 0; j < 26; j++){
            if(randompole[i] == pole[j]){
                count[j]++;
            }
        }
    }*/
   printf("%d == %d", sizeof(count), sizeof(int) * CHAR);
   memset(count, 0, sizeof(count));
   for (int i = 0; randompole[i] != '\0'; i++) {
        count[randompole[i] - 'A']++;
    }

    printf("\n");
    for(int i = 0; i < 26; i++){
        //printf("%c: %d\n", pole[i], count[i]);
        printf("%c: %d\n", 'A' + i, count[i]);
    }
    
    return 0;
}



