#include <stdio.h>

int input(int order)
{
    int number = 0;
    int countOfChar = 0;
    do
    {
        number = 0;
        countOfChar = 0;
        printf("Enter %d. whole number (exept for 0)", order);
        scanf("%d", &number);
        while (getchar() != '\n')
        {
            countOfChar++;
        }
        if (countOfChar != 0)
        {
            printf("You didn't enter whole number, try again.\n");
        }
        else if (number == 0)
        {
            printf("You entered zero, try again.\n");
        }
    } while (number == 0 || countOfChar != 0);
    return number;
}

int multiply(int larger, int smaller){
    while (1){
            if (larger % smaller == 0){
                return smaller;
            } else {
                int multiplies = 1;
                int largerMultiplied = 0;
                do {
                    multiplies++;
                    largerMultiplied = larger * multiplies;
                    if (largerMultiplied % smaller == 0){
                        return largerMultiplied;
                    } else {
                    }
                } while (largerMultiplied%smaller != 0);
            }
            
        }
}

int calculate(int a, int b){
    int answer = 0;
    int largerNum = a > b ? a : b;
    if (largerNum == a){
        answer = multiply(a, b);
    } else {
        answer = multiply(b, a);
    } return answer;
}

int main(){
    int order = 1;
    int a = input(order);
    order++;
    int b = input(order);
    int answer = calculate(a, b);
    printf("The common multiple of %d and %d is %d", a, b, answer);
    return 0;
}