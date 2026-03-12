/*
 * generatorRodnychCisel.c ver. 1.0
 *
 * Generuje rodne cislo na zaklade zadanych 
 * vstupnich parametru (rok, mesic, den, 
 * trojciferny kod a pohlavi).
 * ========================================
 *
 * František Rubáček - 8. 3. 2026
 * 
 */



#include <iostream>
#include <ctime>    // For time() function
#include <limits>   // For input validation
#include "grc.h"    // Include the BirthNumberGenerator class

int main() {
    // Initialize the random number generator
    srand(time(0));
    BirthNumberGenerator generator;
    // Helper variables for keyboard input
    int year, month, day, threeDigits;
    int genderChoice = 0;

    std::cout << "--- GENERATOR RODNEHO CISLA ---\n";

    // Input and validate year, month, day, and three-digit number (checks also for non-integer input)
    do {
        std::cout << "Zadejte rok (1954 - 2053): ";
        if (!(std::cin >> year)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Chybne zadani, zkuste to znovu.\n";
            year = 0;
            continue;
        }
    } while (!generator.setYear(year)); // Repeat until method returns true (until there is a valid input)

    do {
        std::cout << "Zadejte mesic (1 - 12): ";
        if (!(std::cin >> month)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Chybne zadani, zkuste to znovu.\n";
            month = 0;
            continue;
        }
    } while (!generator.setMonth(month));
 
    do {
        std::cout << "Zadejte den: ";
        if (!(std::cin >> day)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Chybne zadani, zkuste to znovu.\n";
            day = 0;
            continue;
        }
    } while (!generator.setDay(day));

    do {
        std::cout << "Zadejte trojcisli (1 - 999): ";
        if (!(std::cin >> threeDigits)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Chybne zadani, zkuste to znovu.\n";
            threeDigits = 0;
            continue;
        }
    } while (!generator.setThreeDigits(threeDigits));

    // Input gender
    while (!generator.setGenderFromInput(genderChoice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Chybne zadani, zkuste to znovu.\n";
    }

    // Generate the identification number (Rodne cislo)
    std::string result = generator.generateBirthNumber();

    // Display result
    std::cout << "\n-------------------------------\n";
    std::cout << "Vygenerovane rodne cislo: " << result << "\n";
    std::cout << "-------------------------------\n";

    return 0;
}
