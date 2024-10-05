/*

Uvod do ukazatelu a alokace pameti, 
par experimentu s ukazateli a 
minihra s polem.

25.9.2024

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Přidání knihovny pro funkci time()

void pointersExperiment()
{
    int number = 10;
    int *pointer = &number;
    // Výpis adresy a hodnoty proměnné number
    printf("Toto je adresa čísla: %p\n"
           "Toto je hodnota čísla: %d\n",
           pointer, *pointer);
    int array[5] = {10, 20, 30, 40, 50};
    // Výpis hodnot z pole array
    printf("Toto je neúspěch provedený úspěšně: %d\n"
           "Toto je cesta: %d\n",
           *array + 1, *(array + 1));
}

int main()
{
    int *pointer = NULL;
    int desiredLength;
    // Dotaz na délku pole od uživatele
    printf("Jak dlouhé chcete pole?\n Zadejte: ");
    scanf("%d", &desiredLength);
    // Alokace paměti pro pole
    pointer = (int *)malloc(desiredLength * sizeof(int));
    if (pointer == NULL)
    {
        // Kontrola, zda alokace paměti byla úspěšná
        printf("Špatný ukazatel\n");
        return 1;
    }
    srand(time(NULL)); // Inicializace generátoru náhodných čísel

    printf("Alokace paměti byla úspěšná\n");
    for (int i = 0; i < desiredLength; i++)
    {
        // Generování náhodných hodnot a jejich uložení do pole
        pointer[i] = rand() % 1000 + 1;
        // Výpis adresy a hodnoty každé pozice v poli
        printf("Adresa pozice pole %d je: %p\n"
               "Její hodnota je: %d\n",
               i, &pointer[i], pointer[i]);
        if (pointer[i] == 1000)
        {
            // Výpis zprávy při dosažení hodnoty 1000
            printf("------------------------------------------------------------------------------------------------------------------\n"
                   "--------------------------------------JACKPOOOOOOOOTTTTTTTT-------------------------------------------------------\n"
                   "------------------------------------------------------------------------------------------------------------------\n");
        }
    }

    free(pointer); // Uvolnění alokované paměti
    return 0;
}