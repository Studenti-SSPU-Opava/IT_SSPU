#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_prime_number(int number) {
    const int sqrt_number = sqrt(number);
    for (int i = 2; i <= sqrt_number; i++)
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
        printf("%d, ", *(array+i));
    }
    printf("\n");
}

int* prime_numbers_finder(int max_number, int *output_length){
    int *array = NULL, array_size = 0;
  
    for (int i = 2; i < max_number; i++)
    {
        if (is_prime_number(i)){
            array = realloc(array, sizeof(int) * (array_size + 1));
            if (array == NULL){
                printf("Memory allocation failed\n");
                return NULL;
            }
            array[array_size++] = i;
        }
    }

    *output_length = array_size;
    return array;
}

int main(){
    int prime_numbers_length;
    int* prime_numbers = prime_numbers_finder(1000, &prime_numbers_length);

    print_int_array(prime_numbers, prime_numbers_length);

    free(prime_numbers);


}