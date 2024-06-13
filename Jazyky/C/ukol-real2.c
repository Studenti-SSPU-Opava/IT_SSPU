#include <stdio.h>

#define MIN 1800
#define MAX 2100

typedef struct {
    int day;
    int month;
    int year;
} DATE;

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

do {
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
    } while (buffer != 0 || num < min || num > max);

    return num;
}


int main() {
    DATE date1;
    DATE date2;
    int daysApart;

    // Get input for both dates, the first three cycles are then added to date 1 and the last three to date 2
    date1.year = input("year", MIN, MAX);
    date1.month = input("month", 1, 12);
    date1.day = input("day", 1, daysInMonth(date1.month, date1.year));

    date2.year = input("year", MIN, MAX);
    date2.month = input("month", 1, 12);
    date2.day = input("day", 1, daysInMonth(date2.month, date2.year));


    printf("The first date is: %d/%d/%d\n", date1.year, date1.month, date1.day);
    printf("The second date is: %d/%d/%d\n", date2.year, date2.month, date2.day);

    // Call out the function to convert the dates into days
    daysApart = dateConvert(date1.year, date2.year, date1.month, date2.month, date1.day, date2.day);
    printf("These two dates are %d days apart from each other.\n", daysApart);
    return 0;
}