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
    int genderChoice = 0;

    std::cout << "--- GENERATOR RODNEHO CISLA ---\n";

    // Input and validate year, month, day, and three-digit number (checks also for non-integer input)
    generator.promptAndSetInput(BirthNumberGenerator::InputType::Year);
    generator.promptAndSetInput(BirthNumberGenerator::InputType::Month);
    generator.promptAndSetInput(BirthNumberGenerator::InputType::Day);
    generator.promptAndSetInput(BirthNumberGenerator::InputType::ThreeDigits);

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
