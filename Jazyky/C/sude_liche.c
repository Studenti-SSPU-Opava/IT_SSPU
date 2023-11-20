#include <stdio.h>

int main() {
    int number;
    int countOfChar;
    do {
        printf("Write a whole number \n");
        scanf("%d", &number);
        countOfChar = 0;
        while (getchar() != '\n') {
            countOfChar++;
        }
        printf("There were %d characters in I/O buffer.\n", countOfChar);
        if (countOfChar != 0) {
            printf("You haven't written a whole number. Try again.\n");
        }
        else if (number == 0) {
            printf("The number is zero. The program will be finished.\n");
        } else if (number % 2 == 0) {
            printf("The number %d is even\n", number);
        } else {
            printf("The number %d is odd.\n", number);
        }
    } while (number != 0);
    return 0;
}
