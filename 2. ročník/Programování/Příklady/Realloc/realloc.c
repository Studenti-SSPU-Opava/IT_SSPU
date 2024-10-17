/*
 * realloc ver. 1.0
 *
 * Program na nalezení prvočísel menších než 1000
 * a jejich výpis
 * =================================
 *
 * v1.0 - Elias Constantine - 16.10.2024
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Funkce pro kontrolu, zda je číslo prvočíslo
int is_prime_number(int number) {
    const int sqrt_number = (int) sqrt(number);
    for (int i = 2; i <= sqrt_number; i++)
    {
        if (number % i == 0){
            return 0; // Číslo není prvočíslo
        }
    }
    return 1; // Číslo je prvočíslo
}

// Funkce pro tisk pole celých čísel
void print_int_array(int* array, int size){
    for (int i = 0; i < size; i++)
    {
        printf("%d, ", *(array+i));
    }
    printf("\n");
}

// Funkce pro nalezení všech prvočísel menších než max_number
int* prime_numbers_finder(int max_number, int *output_length){
    int *array = NULL, array_size = 0;
  
    for (int i = 2; i < max_number; i++)
    {
        if (is_prime_number(i)){
            array = realloc(array, sizeof(int) * (array_size + 1));
            if (array == NULL){
                printf("Memory allocation failed\n");
                return NULL; // Alokace paměti selhala
            }
            array[array_size++] = i; // Přidání prvočísla do pole
        }
    }

    *output_length = array_size; // Nastavení délky výstupního pole
    return array; // Vrácení pole prvočísel
}

int main(){
    int prime_numbers_length;
    int* prime_numbers = prime_numbers_finder(1000, &prime_numbers_length);

    print_int_array(prime_numbers, prime_numbers_length); // Tisk nalezených prvočísel

    free(prime_numbers); // Uvolnění alokované paměti
}