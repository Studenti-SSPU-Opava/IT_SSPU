/*Napište program v jazyce C, který přečte z textového souboru cisla.txt dvojice čísel a zjistí jejich
nejmenší společný násobek a největší společný dělitel. Výsledky budou vypsány na obrazovku a do
textového souboru vystup.txt dle vzoru.
*/

#include <stdio.h>
#define SOUBOR "cisla.txt"
#define VYSTUP "vystup.txt"

// Funkce pro výpočet nejmenšího společného dělitele
int nsd(int a, int b)
{
    int c;
    while (b != 0)
    {
        c = a % b;
        a = b;
        b = c;
    }
    return a;
}

// Funkce pro výpočet nejmešího společného násobku
int nsn(int a, int b)
{
    return a * b / nsd(a, b);
}

// Funkce pro výpis hlavičky do console
void hlavicka()
{
    printf("Vypis cisel ze souboru cisla.txt\n");
    printf("--------------------------------\n");
    printf("poradi  cislo1\tcislo2\tnsn\tnsd\n");
}

// Funkce pro výpis hlavičky do souboru
void hlavickaVystup(FILE *file)
{
    fprintf(file, "Vypis delitelnych cisel ze souboru cisla.txt\n");
    fprintf(file, "--------------------------------------------\n");
    fprintf(file, "poradi  cislo1\tcislo2\tnsn\tnsd\n");
}

int main()
{
    FILE *file;//Otevření souboru cisla.txt
    file = fopen(SOUBOR, "r");
    if (file == NULL)
    {
        printf("Soubor se nepodarilo otevrit\n");
        return 1;
    }
    FILE *fileOut;//Otevření souboru vystup.txt
    fileOut = fopen(VYSTUP, "w");
    if (fileOut == NULL)
    {
        printf("Soubor se nepodarilo otevrit\n");
        return 1;
    }

    hlavicka();
    hlavickaVystup(fileOut);
    int a = 0, b = 0;
    int i = 1;
    int y = 1;
    float sum = 0;
    float sum2 = 0;
    while (fscanf(file, "%d %d", &a, &b) != EOF)//Čtení ze souboru
    {
        // Přičtení hodnoty a do sumy pro výpočet průměru
        sum += a;
        printf("%d.\t%d\t%d\t%d\t%d\n", i, a, b, nsn(a, b), nsd(a, b));
        if (nsd(a, b) > 1)
        {
            fprintf(fileOut, "%d.%8d%8d%8d%4d\n", y, a, b, nsn(a, b), nsd(a, b));
            sum2 += a;
            y++;
        }
        i++;
    }

    printf("Prumer cisel v prvnim sloupci je: %.2f\n", sum / (i - 1));//Výpočet průměru
    printf("\nSoubor cisla.txt obsahuje %d dvojic cisel\n", i - 1);//Počet dvojic čísel
    printf("\nByl vytvoren soubor vystup.txt\n");//Informace o vytvoření souboru
    fprintf(fileOut, "Prumer cisel v prvnim sloupci je: %.2f\n", sum2 / (y - 1));//Výpočet průměru do souboru
    fprintf(fileOut, "\nSoubor cisla.txt obsahuje %d dvojic cisel\n", y - 1);//Počet dvojic čísel do souboru

    if (fclose(file) == EOF)//Zavření souboru cisla.txt
    {
        printf("Soubor se nepodarilo zavrit\n");
        return 1;
    }
    if (fclose(fileOut) == EOF)//Zavření souboru vyjstup.txt
    {
        printf("Soubor se nepodarilo zavrit\n");
        return 1;
    }
    return 0;
}
