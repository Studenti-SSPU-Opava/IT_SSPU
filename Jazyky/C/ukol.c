#include <stdio.h>

int isLeapYear(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        return 1;
    }
    return 0;
}

int getDaysInMonth(int month, int year) {
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year)) {
        return 29;
    }
    return daysInMonth[month - 1];
}

int countDays(int day1, int month1, int year1, int day2, int month2, int year2) {
    int days = 0;

    while (year1 < year2 || (year1 == year2 && month1 < month2) || (year1 == year2 && month1 == month2 && day1 < day2)) {
        days++;
        day1++;
        if (day1 > getDaysInMonth(month1, year1)) {
            day1 = 1;
            month1++;
            if (month1 > 12) {
                month1 = 1;
                year1++;
            }
        }
    }

    return days;
}

int main() {
    int day1, month1, year1;
    int day2, month2, year2;

    printf("Enter the first date (day month year): ");
    scanf("%d %d %d", &day1, &month1, &year1);

    printf("Enter the second date (day month year): ");
    scanf("%d %d %d", &day2, &month2, &year2);

    if (year1 < 1800 || year2 > 2100) {
        printf("Invalid year! Year must be between 1800 and 2100.\n");
        return 1;
    }

    int days = countDays(day1, month1, year1, day2, month2, year2);
    printf("Number of days between the two dates: %d\n", days);

    return 0;
}