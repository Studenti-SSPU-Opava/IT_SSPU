//
// Created by iqmas on 08.03.2026.
//

#ifndef BIRTH_NUMBER_GENERATOR_H
#define BIRTH_NUMBER_GENERATOR_H

#include <string>

class BirthNumberGenerator {
public:
    enum class InputType {
        Year,
        Month,
        Day,
        ThreeDigits
    };
    BirthNumberGenerator();
    ~BirthNumberGenerator();
    std::string generateBirthNumber();
    bool setYear(int year);
    bool setMonth(int month);
    bool setDay(int day);
    bool setThreeDigits(int threeDigits);
    bool setGenderFromInput();
    void promptAndSetInput(InputType type);
private:
    int day;
    int month;
    int year;
    int threeDigits;
    bool isFemale;
};

bool promptRepeat();

#endif // BIRTH_NUMBER_GENERATOR_H
