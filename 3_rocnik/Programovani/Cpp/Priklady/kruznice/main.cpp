#include <iostream>
#include "bod.h"
#include "kruznice.h"

void vypis(const kruznice &k, int cislo) {
    std::cout << "Kruznice k" << cislo << " ma polomer " << k.get_r() << ", prumer " << k.prumer() << ", obvod "
              << k.obvod()
              << " a obsah " << k.obsah() << std::endl;
}

int main() {
    kruznice k1(3);
    kruznice k2(1.2);
    kruznice k3(k1);
    kruznice k4;
    float r;
    vypis(k1, 1);
    vypis(k2, 2);
    vypis(k3, 3);
    vypis(k4, 4);
    std::cout << "Zadejte polomer kruznice: " << std::endl;
    std::cin >> r;
    if (k1.set_r(r)) {
        vypis(k1, 1);
    } else {
        std::cout << "Chybne zadani polomeru" << std::endl;
    }



    return 0;
}