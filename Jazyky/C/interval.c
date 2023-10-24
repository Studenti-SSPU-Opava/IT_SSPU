#include <stdio.h>

#define MIN 1 //definuje konstantu MIN
#define MAX 100 //definuje konstantu MAX

int main()
{
    int zadaneCislo, countOfChar; //vytvoří proměnné zadaneCislo a countOfChar
    do 
    {
        printf("Zadej cislo intervalu od %d do %d\n", MIN, MAX); //vypíše zprávu do terminálu
        scanf("%d", &zadaneCislo); //čeká na vstup od uživatele
        countOfChar = 0; //nastaví countOfChar na 0 (aby nezůstala plná po opakování)
        while (getchar() != '\n') //maže po jednom znaky z I/O bufferu, dokud v něm nic nezůstane
        {
            countOfChar++; //při každém vymazání jednoho znaku přičte 1 k countOfChar
        }
        if (countOfChar != 0) //pokud countOfChar byla větší než 0 (tzn. buffer nebyl prázdný)
        {
            printf("Nezadal jsi spravne cislo, zadej znovu.\n"); //vypíše zprávu do terminálu
        }
        else if (zadaneCislo < MIN || zadaneCislo > MAX) //pokud je cislo mimo rozsah
        {
            printf("nezadal jsi cislo v intervalu, zadej ho znovu.\n"); //vypíše zprávu do terminálu
        }
    } while (countOfChar != 0 || zadaneCislo < MIN || zadaneCislo > MAX); //opakuje, pokud zadaneCislo neni mezi hodnotami MIN a MAX a zároveň countOfChar byla 0 (v bufferu nic nebylo)
    printf("Cislo %d je v intervalu %d-%d.\n",zadaneCislo,MIN,MAX); //vypíše zprávu do terminálu
    return 0;
}