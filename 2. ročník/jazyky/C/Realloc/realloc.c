#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_prime_number(int number) {
    const int sqrt_number = sqrt(number);
    for (int i = 0; i <= number; i++)
    {
        if (number % i == 0){
            return 0;
        }
    }
    return 1;
}

void print_int_array(int* array, int size){
    for (int i = 0; i < size; i++)
    {
        printf("%d\n", array[i]);
    }
}

int main(){
    int* prime_numbers = NULL;
    int prime_numbers_size = 0;
    int index = 2;

    while (1)
    {
        if (is_prime_number(++index)){
            prime_numbers = realloc(prime_numbers, 
                sizeof(int) * prime_numbers_size);
            if (prime_numbers == NULL){
                printf("Memory allocation failed\n");
                return 1;
            }
            prime_numbers[prime_numbers_size++] = index;
            
            printf("Prime number: %d\n", index);
            print_int_array(prime_numbers, prime_numbers_size);
        }
    }
    index++;
}