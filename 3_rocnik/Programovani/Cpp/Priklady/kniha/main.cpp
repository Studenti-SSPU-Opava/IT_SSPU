#include <iostream> // vstup/vystup
#include <string> // retezce

#include "kniha.h" // trida Kniha

void printHeader(const std::string &title) { // vypis nadpisu
    std::cout << title << "\n"; // nadpis
    std::cout << std::string(title.size(), '-') << "\n"; // oddelovaci cara
} // konec funkce

void printKnihaBlock(const std::string &title, const Kniha &kniha) { // vypis celeho bloku
    printHeader(title); // nadpis
    std::cout << kniha << "\n"; // obsah knihy
} // konec funkce

std::string readLine(const std::string &prompt) { // cteni radku
    std::cout << prompt; // vypsat vyzvu
    std::string input; // vstup
    std::getline(std::cin, input); // nacteni radku
    return input; // vratit retezec
} // konec funkce

bool readBookFromUser(Kniha &kniha) { // zadavani knihy
    while (true) { // opakovani dokud nezruseno
        std::string isbn = readLine("ISBN\n: "); // zadani ISBN
        std::string autor = readLine("Autor (3 az 100) znaku: "); // zadani autora
        std::string nazev = readLine("Nazev (3 az 100) znaku: "); // zadani nazvu

        if (kniha.setKniha(isbn, autor, nazev)) { // pokus o ulozeni
            return true; // uspesne
        }

        std::cout << "Chybne zadane udaje." << "\n"; // chyba
        std::string volba = readLine("Pokracovat v zadavani? (a/n): "); // dotaz
        if (!volba.empty() && (volba[0] == 'n' || volba[0] == 'N')) { // kontrola odpovedi
            return false; // ukonceni
        }
    }
} // konec funkce

int main() { // hlavni funkce
    Kniha k1; // objekt vychozi
    Kniha k2("978-80-251-1583-1", "Jesse Liberty", "Naucte se C++ za 21 dni"); // objekt s parametry
    Kniha k3(k2); // kopirovaci konstruktor

    printKnihaBlock("Objekt k1 vytvoreny vychozim konstruktorem", k1); // vypis k1
    printKnihaBlock("Objekt k2 vytvoreny konstruktorem s parametry", k2); // vypis k2
    printKnihaBlock("Objekt k3 vytvoreny kopirovacim konstruktorem", k3); // vypis k3

    printHeader("Zadani udaju o knize"); // zacatek vstupu
    if (readBookFromUser(k1)) { // nacteni od uzivatele
        printKnihaBlock("Objekt k1 po zmene", k1); // vypis po zmene
    }

    return 0; // konec programu
} // konec main
