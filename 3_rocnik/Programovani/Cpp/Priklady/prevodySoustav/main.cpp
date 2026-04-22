#include "ps.h"
#include <iostream>
#include <limits>

int zadaniSoustavy(){
    int zaklad;
    do {
        std::cout << "Zadejte zaklad soustavy od" << Soustavy::MIN_ZAKLAD << " do " << Soustavy::MAX_ZAKLAD << ": ";
        std::cin >> zaklad;
        if (std::cin.fail() || zaklad < Soustavy::MIN_ZAKLAD || zaklad > Soustavy::MAX_ZAKLAD) {
            std::cout << "Neplatný vstup. Používám výchozí hodnotu " << Soustavy::MIN_ZAKLAD << "." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Odstraní neplatný vstup z bufferu
            std::cin.clear(); // Vyčistí chybový stav
            return Soustavy::MIN_ZAKLAD;
        } else if (zaklad < Soustavy::MIN_ZAKLAD || zaklad > Soustavy::MAX_ZAKLAD) {
            std::cout << "Neplatný vstup. Používám výchozí hodnotu " << Soustavy::MIN_ZAKLAD << "." << std::endl;
            return Soustavy::MIN_ZAKLAD;
        } else {
            return zaklad;
        }
    } while (true);

    return zaklad;
}


string zadaniCisla(int zaklad) {
    string cislo;
    do {
        std::cout << "Zadejte cislo v soustave o zakladu " << zaklad << ": ";
        std::getline(std::cin, cislo);
        if (!Soustavy::platnostCisla(cislo, zaklad)) {
            std::cout << "Neplatný vstup. Zkuste to znovu." << std::endl;
        }
    } while (!Soustavy::platnostCisla(cislo, zaklad));
    return cislo;
}

int main() {
    
    Soustavy s1;
    Soustavy s2("1010", 2);
    Soustavy s3("ABCD", 16);
    Soustavy s4(s3);
    std::cout << "objekt vytvoren pomoci bezparametrickeho konstruktoru: " << std::endl;
    std::cout << s1 << std::endl;
    std::cout << "objekt vytvoren pomoci konstruktoru s parametry: " << std::endl;
    std::cout << s2 << std::endl;
    std::cout << "objekt vytvoren pomoci konstruktoru s parametry: " << std::endl;
    std::cout << s3 << std::endl;
    std::cout << "objekt vytvoren pomoci konstruktoru pro kopirovani: " << std::endl;
    std::cout << s4 << std::endl;    
    return 0;
}
