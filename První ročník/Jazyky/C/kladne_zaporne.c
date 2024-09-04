#include <stdio.h>

int main() {
    int number = 0; //vytvori promennou s nazvem "number"
    int pocetOpakovani = 0; //vytvori promennou s nazvem "pocetOpakovani" s obsahem 0
    // proměnná pro uložení návratové hodnoty funkce scanf
    int returnValue;
    int countOfChar; // počet znaků ve v/v bufferu
    do {
        pocetOpakovani++;
        printf("%d Write a whole number:\n(Write 0 for exit)\n", pocetOpakovani);
        /*napise do konzole text a promennou pocetOpakovani
        *zpetne lomitko: Alt Gr + Q */
        returnValue = scanf("%d", &number); //pocka na zadani uzivatele
        /* Pokud uživatel nezadá celé číslo, funkce scanf vrátí nulu. Zadané znaky zůstanou
         * ve v/v bufferu. Pokud v/v buffer obsahuje znaky, funkce scanf nepozastaví konzoli,
         * uživatel nemá možnost zadat nové číslo. Důsledkem je nekonečný cyklus. */
        printf("Navratova hodnota funkce scanf je %d.\n", returnValue);
        /* Funkce getchar() přečte jeden znak z v/v bufferu a záveň jej vymaže. Každý uživatelský vstup je
         * ukončen klávesou Enter ('\n'). Čtení a výmaz znaků probíhá zatímco znak se nerovná klávese Enter. */
        countOfChar = 0; // do proměnné countOfChar uložíme hodnotu 0
        while (getchar() != '\n') {
            /* hodnotu proměnné countOfChar zvýším o jedničku*/
            countOfChar++;
        }
        printf("Ve v/v bufferu bylo nalezeno %d znaku.\n", countOfChar);
        if (countOfChar != 0) {
            printf("Nezadal jsi cele cislo. Zadej znovu.\n");
        } else if (number > 0) { //pokud je cislo vetsi nez nula
            printf("The number %d is positive.\n\n", number); //napise do konzole
        } else if (number == 0) {
            /*pokud se rovna nula
            *(musi byt 2× =, jelikoz 1× = se pouziva pro promenne)*/
            printf("The number is zero.\n\n"); //napise do konzole

        } else { //jinak
            printf("The number %d is negative\n\n", number); //napise do konzole
        }
    } while (number != 0 || countOfChar != 0); // opakuje pokud se nerovna nule (!= znamena nerovna se)
    return 0;
}
