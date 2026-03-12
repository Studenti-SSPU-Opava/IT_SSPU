//
// Created by iqmas on 08.02.2026.
//

#include "grc.h"

#include <cstdlib>
#include <iostream>
#include <string>


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
    day = dayInput;
    if (day > 31) {
        return false;
    } else if (day == 31 && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)) {
        return true;
    } else if (day == 30 && (month == 4 || month == 6 || month == 9 || month == 11)) {
        return true;
    } else if (day == 29 && month == 2 && (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))) {
        return true;
    } else if (day == 28 && month == 2) {
        return true;
    } else if (day >= 1 && day <= 28) {
        return true;
    } else {
        return false;
    }
}

// Validate and set month (1-12)
bool BirthNumberGenerator::setMonth(int monthInput) {
    month = monthInput;
    if (month <= 0 || month > 12) {
        return false;
    } else {
        return true;
    }
}

// Validate and set year (1954-2053)
bool BirthNumberGenerator::setYear(int yearInput) {
    year = yearInput;
    if (year < 1954 || year > 2053) {
        return false;
    } else {
        return true;
    }
}

// Validate and set sequence digits (1-1000)
bool BirthNumberGenerator::setThreeDigits(int threeDigitsInput) {
    threeDigits = threeDigitsInput;
    if (threeDigits <= 0 || threeDigits > 1000) {
        return false;
    } else {
        return true;
    }
}

// Prompt user to input gender and set accordingly
bool BirthNumberGenerator::setGenderFromInput(int genderChoice) {
    std::cout << "Zadejte cislo 0 (muz) nebo 1 (zena):" << std::endl;
    std::cin >> genderChoice;
    if (genderChoice == 1) {
        isFemale = true;
        return true;
    } else if (genderChoice == 0) {
        isFemale = false;
        return true;
    } else {
        return false;
    }
}
