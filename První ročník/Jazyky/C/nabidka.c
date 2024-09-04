#include <stdio.h>
#include <math.h>

#define POCETVOLEB 6

int main()
{
    int volba;
    int countOfChar;
    float r = 2.54;

    printf("1 - zadani polomeru\n");
    printf("2 - obvod kruhu\n");
    printf("3 - obsah kruhu\n");
    printf("4 - objem koule\n");
    printf("5 - povrch koule\n");
    printf("6 - konec programu\n");
    do
    {
        printf("Zadejte volbu v intervalu 1-%d:", POCETVOLEB);
        scanf("%d", &volba);
        countOfChar = 0;
        while (getchar() != '\n')
        {
            countOfChar++;
        }
        if (countOfChar != 0)
        {
            // nastaveni proměnné volba na neplatnou hodnotu
            volba = POCETVOLEB + 1;
        }
        if (volba < 1 || volba > POCETVOLEB)
        {
            printf("Chybna volba, zadej znovu.\n");
        }
    } while (volba < 1 || volba > POCETVOLEB);
    switch (volba)
    {
    case 1:
        printf("Hodnota polomeru %.2f je %.2f.\n", r, r);
        break;
    case 2:
        printf("Obvod o polomeru %.2f je %.2f.\n", r, 2 * M_PI * r);
        break;
    case 3:
        printf("Obsah o polomeru %.2f je %.2f.\n", r, M_PI * r * r);
        break;
    case 4:
        printf("Objem o polomeru %.2f je %.2f.\n", r, 4.0 / 3.0 * M_PI * r * r * r);
        break;
    case 5:
        printf("Povrch o polomeru %.2f je %.2f.\n", r, 4 * M_PI * r * r);
        break;
    case 6:
        printf("Program bude ukoncen.\n");
        break;
    default:
    }
}
return 0;
}