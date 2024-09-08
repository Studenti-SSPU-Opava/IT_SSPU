#include <stdio.h>
#include <stdlib.h>

#define MAX_HOD 23
#define MAX_MIN_SEC 59

int vstup(const char *text, int poradi, int max)
{
    int cislo;
    int countOfChar;
    do
    {
        printf("CAS %d:Zadej %s v intervalu 0-%d: ", poradi, text, max);
        scanf("%d", &cislo);
        countOfChar = 0;
        while (getchar() != '\n')
        {
            countOfChar++;
        }
        if (countOfChar != 0)
        {
            printf("CHYBA: %s nebyly zadany jako cele cislo. Zadej znovu.\n", text);
        }
        else if (cislo < 0 || cislo > max)
        {
            printf("CHYBA: %s Nebyly zadany v intervalu od 0 do %d. Zadej znovu.\n", text, max);
        }

    } while (countOfChar != 0 || cislo < 0 || cislo > max);
    return cislo;
}

int sekundyOdPulnoci(int hodiny, int minuty, int sekundy)
{
    return hodiny * 3600 + minuty * 60 + sekundy;
}

int ziskejCas(int poradi)
{
    int hodiny, minuty, sekundy, cas;
    hodiny = vstup("hodiny", poradi, MAX_HOD);
    minuty = vstup("minuty", poradi, MAX_MIN_SEC);
    sekundy = vstup("sekundy", poradi, MAX_MIN_SEC);
    printf("Zadal jsi cas: %02d:%02d:%02d\n", hodiny, minuty, sekundy);
    cas = sekundyOdPulnoci(hodiny, minuty, sekundy);
    printf("Od pulnoci ubehlo %d sekund.\n", cas);
    return cas;
}

int opakuj()
{
    int klavesa;
    int countOfChar = 0;
    printf("Chcete zadat cas znovu? Stisknete Z: ");
    klavesa = getchar();
    while (getchar() != '\n')
    {
        countOfChar++;
    }
    if (countOfChar != 0)
    {
        return 0;
    }
    if (klavesa == 'Z' || klavesa == 'z')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    int cas1, cas2;
    do
    {
        cas1 = ziskejCas(1);
        cas2 = ziskejCas(2);
        if (cas1 > cas2)
        {
            printf("Cas 1 je vetsi nez cas 2.\n");
        }
        else if (cas1 < cas2)
        {
            printf("Cas 2 je vetsi nez cas 1.\n");
        }
        else
        {
            printf("Cas 1 je stejny jako cas 2.\n");
        }

        printf("Rozdil mezi casem 1 a casem 2 je %d sekund.\n", abs(cas1 - cas2));
    } while (opakuj());
    return 0;
}