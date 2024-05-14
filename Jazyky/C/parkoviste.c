#include <stdio.h>

int vypocet() {
    int cas = zadani();
    int penize = 0;
    int minuty = cas / 60;
    if (minuty < 15) {
        penize = 0;
    } else if (minuty < 30) {
        penize = 10;
    } else if (minuty < 60) {
        penize = 20;
    } else {
        penize = 30;
    }
    return penize;
}

int zadani() {
    int cas = 0;
    printf("Zadejte cas parkovani (sekundy): ");
    scanf("%d", &cas);
    return cas;
}


int odpoved() {
    int penize = vypocet();
    printf("Zaplatite: %d Kc\n", penize);
}

int main() {
    odpoved();
    return 0;
}