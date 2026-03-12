//
// Created by iqmas on 08.03.2026.
//

#ifndef BIRTH_NUMBER_GENERATOR_H
#define BIRTH_NUMBER_GENERATOR_H

#include <string>

class BirthNumberGenerator {
public:
    BirthNumberGenerator();
    ~BirthNumberGenerator();
    std::string generateBirthNumber();
    bool setYear(int year);
    bool setMonth(int month);
    bool setDay(int day);
    bool setThreeDigits(int threeDigits);
    bool setGenderFromInput(int genderChoice);
private:
    int day;
    int month;
    int year;
    int threeDigits;
    bool isFemale;
};

#endif // BIRTH_NUMBER_GENERATOR_H
