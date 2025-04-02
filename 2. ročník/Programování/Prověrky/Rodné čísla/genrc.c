#include <stdio.h>
#include <time.h>

#define ROKMIN 1900
#define ROKMAX 2100

int main() {
    int rok, mesic, den;
    struct tm timeinfo = {0};
    time_t t;

    while (1) {
        printf("Zadejte rok narození (RRRR): ");
        scanf("%d", &rok);
        if (rok >= ROKMIN && rok <= ROKMAX) break;
        printf("Rok musí být v rozmezí %d-%d\n", ROKMIN, ROKMAX);
    }

    while (1) {
        printf("Zadejte měsíc narození (MM): ");
        scanf("%d", &mesic);
        if (mesic >= 1 && mesic <= 12) break;
        printf("Měsíc musí být v rozmezí 1-12\n");
    }

    while (1) {
        printf("Zadejte den narození (DD): ");
        scanf("%d", &den);
        
        // Validate day using mktime
        timeinfo.tm_year = rok - 1900;
        timeinfo.tm_mon = mesic - 1;
        timeinfo.tm_mday = den;
        
        t = mktime(&timeinfo);
        if (t != -1 && timeinfo.tm_mday == den) {
            break;
        }
        
        printf("Neplatné datum! Zkuste znovu.\n");
    }

    printf("Platné datum: %04d-%02d-%02d\n", rok, mesic, den);
    return 0;
}
