#include <stdio.h>

#define MIN 1800
#define MAX 2100

int leapYear(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

int daysInMonth(int month, int year) {
    if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
        return 31;
    } else if (month == 9 || month == 4 || month == 6 || month == 11) {
        return 30;
    } else if (leapYear(year)) {
        return 29;
    } else {
        return 28;
    }
}

int dateConvert(int year1, int year2, int month1, int month2, int day1, int day2) {
    int days = 0;

    for (int year = year1 + 1 ; year < year2; year++){
        if (leapYear(year)) {
            days += 366;
        } else {
            days += 365;
        }
    }

    for (int month = month1 + 1; month <= 12; month++) {
        days += daysInMonth(month, year1);
    }
    days += daysInMonth(month1, year1) - day1;

    for (int month = 1; month < month2; month++) {
        days += daysInMonth(month, year2);
    }
    days += day2;

    return days;
}

int input(char *prompt, int min, int max) {
    int buffer;
    int num;

do{
    printf("Enter the %s(%d-%d):", prompt, min, max);
    scanf("%d", &num);

    buffer = 0;

    while (getchar() != '\n') {
        buffer++;
    }

    if (buffer != 0){
        printf("Invalid input. Please try again.\n");
    } else if (num < min || num > max) {
        printf("Invalid input. Please try again.\n");
    } 
}while (/* condition */)
{
    /* code */
}

    return num;
}
int main() {
    printf("Hello, World!\n");
    return 0;
}