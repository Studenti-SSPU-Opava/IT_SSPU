#include <iostream>
#include <ctime>    // Pro time()
#include "grc.h"

int main() {
    // Inicializace generátoru náhodných čísel (stačí zavolat jednou na začátku)
    srand(time(0));

    // Vytvoření objektu tvé třídy
    grc rcGen;

    // Pomocné proměnné pro načítání z klávesnice
    int r, m, d, t;
    int p = 0; // Pro pohlaví

    std::cout << "--- GENERATOR RODNEHO CISLA ---\n";

    // 1. Načtení a kontrola roku
    do {
        std::cout << "Zadejte rok (1954 - 2053): ";
        std::cin >> r;
    } while (!rcGen.get_r(r)); // Opakuj, dokud metoda vrací false

    // 2. Načtení a kontrola měsíce
    do {
        std::cout << "Zadejte mesic (1 - 12): ";
        std::cin >> m;
    } while (!rcGen.get_m(m));

    // 3. Načtení a kontrola dne (musí být až po roce a měsíci kvůli přestupným rokům)
    do {
        std::cout << "Zadejte den: ";
        std::cin >> d;
    } while (!rcGen.get_d(d));

    // 4. Načtení a kontrola trojčíslí
    do {
        std::cout << "Zadejte trojcisli (1 - 999): ";
        std::cin >> t;
    } while (!rcGen.get_t(t));

    // 5. Načtení pohlaví (tvoje metoda má uvnitř vlastní cout a cin, takže ji jen zavoláme)
    while (!rcGen.get_p(p)) {
        std::cout << "Chybne zadani, zkuste to znovu.\n";
    }

    // 6. Generování
    // Poznámka: Posíláme nuly, protože tvoje metoda vygenerujRC ignoruje parametry
    // a rovnou si bere data z privátních proměnných (den, mesic, atd.).
    std::string vysledek = rcGen.vygenerujRC(0, 0, 0, 0);

    // 7. Výpis
    std::cout << "\n-------------------------------\n";
    std::cout << "Vygenerovane rodne cislo: " << vysledek << "\n";
    std::cout << "-------------------------------\n";

    return 0;
}