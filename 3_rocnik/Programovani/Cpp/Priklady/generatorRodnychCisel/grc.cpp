//
// Created by iqmas on 08.02.2026.
//

#include "grc.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

namespace {
bool parseIntStrict(const std::string& line, int& value) {
    // Strict integer parse: reject decimals and trailing characters.
    // basically checks if the entire line is a valid integer.
    std::istringstream iss(line);
    iss >> value;
    if (iss.fail()) {
        return false;
    }
    char extra = 0;
    if (iss >> extra) {
        return false;
    }
    return true;
}

int maxDayInMonth(int month, int year) {
    // Month length with leap-year handling.
    if (month == 2) {
        bool leap = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
        return leap ? 29 : 28;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    return 31;
}

int readIntWithPrompt(const std::string& prompt, int minValue, int maxValue) {
    // Read whole line to avoid leftover input and infinite loops on bad input. Also cheks if the input is an integer and within the specified range.
    int value = 0;
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) {
            std::cin.clear();
            continue;
        }

        if (!parseIntStrict(line, value)) { //tests the validity of a string as an integer and checks for trailing characters
            std::cout << "Chybne zadani, zkuste to znovu.\n";
            continue;
        }

        if (value < minValue || value > maxValue) {
            std::cout << "Chybne zadani, zkuste to znovu.\n";
            continue;
        }

        return value;
    }
}
}

bool promptRepeat() {
    // Loop until user explicitly chooses 1 or 0.
    int choice = readIntWithPrompt(
        "Chcete vygenerovat dalsi rodne cislo? (1 = ano, 0 = ne): ",
        0,
        1);
    return choice == 1;
}


// Constructor - Initialize default Czech birth number values
BirthNumberGenerator::BirthNumberGenerator() {
    day = 28;
    month = 12;
    year = 2010;
    threeDigits = 987;
    isFemale = false;
}

// Destructor
BirthNumberGenerator::~BirthNumberGenerator() {
}

// Generate a valid 10-digit Czech birth number with check digit
std::string BirthNumberGenerator::generateBirthNumber() {
    long long birthNumber = 0;
    int remainder;
    // Loop until we get a valid check digit (remainder != 10)
    do {
        int yearSuffix = (year % 100);  // Last 2 digits of year
        int dayNumber = day;
        // For females, add 50 to month number
        int monthNumber = isFemale ? (month + 50) : month;
        int sequence = threeDigits;

        // Build 9-digit number: YYMMDDXXX (X = sequence)
        birthNumber = yearSuffix * 10000000 + monthNumber * 100000 + dayNumber * 1000 + sequence;
        // Calculate check digit: remainder of division by 11
        remainder = static_cast<int>(birthNumber % 11);
        // If remainder is 10, generate new sequence and retry
        if (remainder == 10) {
            // Czech birth numbers cannot end with remainder 10; retry with new sequence.
            std::cout << "Zbytek po deleni 11 je 10, generuji nove trojcisli.\n";
            sequence = (std::rand() % 1000);
            threeDigits = sequence; // prevent infinite loop
        }
    } while (remainder == 10);

    // Append check digit as 10th digit
    birthNumber = (birthNumber * 10) + remainder;
    return std::to_string(birthNumber);
}

// Validate and set day (1-31, considering month and leap years)
bool BirthNumberGenerator::setDay(int dayInput) {
    int maxDay = maxDayInMonth(month, year);
    if (dayInput < 1 || dayInput > maxDay) {
        return false;
    }
    day = dayInput;
    return true;
}

// Validate and set month (1-12)
bool BirthNumberGenerator::setMonth(int monthInput) {
    if (monthInput <= 0 || monthInput > 12) {
        return false;
    }
    month = monthInput;
    return true;
}

// Validate and set year (1954-2053)
bool BirthNumberGenerator::setYear(int yearInput) {
    if (yearInput < 1954 || yearInput > 2053) {
        return false;
    }
    year = yearInput;
    return true;
}

// Validate and set sequence digits (1-1000)
bool BirthNumberGenerator::setThreeDigits(int threeDigitsInput) {
    if (threeDigitsInput <= 0 || threeDigitsInput > 999) {
        return false;
    }
    threeDigits = threeDigitsInput;
    return true;
}

// Prompt user to input gender and set accordingly
bool BirthNumberGenerator::setGenderFromInput() {
    // Uses strict input to avoid leftover characters in the stream.
    int genderChoice = readIntWithPrompt("Zadejte cislo 0 (muz) nebo 1 (zena): ", 0, 1);
    isFemale = (genderChoice == 1);
    return true;
}

// Prompt for an integer input and set the corresponding field
void BirthNumberGenerator::promptAndSetInput(InputType type) {
    bool isValid = false;

    do {
        int value = 0;
        switch (type) {
            case InputType::Year:
                value = readIntWithPrompt("Zadejte rok (1954 - 2053): ", 1954, 2053);
                break;
            case InputType::Month:
                value = readIntWithPrompt("Zadejte mesic (1 - 12): ", 1, 12);
                break;
            case InputType::Day:
                value = readIntWithPrompt(
                    "Zadejte den (1 - " + std::to_string(maxDayInMonth(month, year)) + "): ",
                    1,
                    maxDayInMonth(month, year));
                break;
            case InputType::ThreeDigits:
                value = readIntWithPrompt("Zadejte trojcisli (1 - 999): ", 1, 999);
                break;
        }

        switch (type) {
            case InputType::Year:
                isValid = setYear(value);
                break;
            case InputType::Month:
                isValid = setMonth(value);
                break;
            case InputType::Day:
                isValid = setDay(value);
                break;
            case InputType::ThreeDigits:
                isValid = setThreeDigits(value);
                break;
        }

        if (!isValid) {
            std::cout << "Chybne zadani, zkuste to znovu.\n";
        }
    } while (!isValid);
}
