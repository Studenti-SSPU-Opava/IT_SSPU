#include <stdio.h>

int cteni(int prvniDruhy){
    struct Datum {
        int rok;
        int mesic;
        int den;
    };
    
    struct Datum datum;
    
    printf("Zadejte %d. rok: ", prvniDruhy);
    scanf("%d", &datum.rok);
    printf("Zadejte %d. mesic: ", prvniDruhy);
    scanf("%d", &datum.mesic);
    printf("Zadejte %d. den: ", prvniDruhy);
    scanf("%d", &datum.den);

    return &datum;
}


int vypocetDnu(int prvniDruhy) {
    struct Datum {
        int rok;
        int mesic;
        int den;
    };
    
    struct Datum datum;

    datum = cteni(prvniDruhy);
    int dny = datum.den + datum.mesic * 30 + datum.rok * 365;
    
}

int vypocetRozdilu() {
    int datum1 = vypocetDnu(1);
    int datum2 = vypocetDnu(2);
}


int main() {
    int vypocetRozdilu();
    return 0;
}