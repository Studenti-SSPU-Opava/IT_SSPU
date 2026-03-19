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
#include "grc.h"    // Include the BirthNumberGenerator class

int main() {
    // Initialize the random number generator
    srand(time(0));
    std::cout << "--- GENERATOR RODNEHO CISLA ---\n";

    bool again = true;
    while (again) {
        // New instance keeps state clean per run.
        BirthNumberGenerator generator;

        // Input and validate year, month, day, and three-digit number (checks also for non-integer input)
        generator.promptAndSetInput(BirthNumberGenerator::InputType::Year);
        generator.promptAndSetInput(BirthNumberGenerator::InputType::Month);
        generator.promptAndSetInput(BirthNumberGenerator::InputType::Day);
        generator.promptAndSetInput(BirthNumberGenerator::InputType::ThreeDigits);

        // Input gender
        generator.setGenderFromInput();

        // Generate the identification number (Rodne cislo)
        std::string result = generator.generateBirthNumber();

        // Display result
        std::cout << "\n-------------------------------\n";
        std::cout << "Vygenerovane rodne cislo: " << result << "\n";
        std::cout << "-------------------------------\n";

        again = promptRepeat(); // if user want to run the app again
    }

    return 0;
}
