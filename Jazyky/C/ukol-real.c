#include <stdio.h>

// Define the minimum and maximum years
#define MIN 1800
#define MAX 2100

typedef struct {
    int day;
    int month;
    int year;
} DATE;

// Function to check the number of days in a given month of a year
int daysInMonth(int month, int year) {
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
        return 31;
    } else if (month == 9 || month == 4 || month == 6 || month == 11) {
        return 30;
    } else if (leapYear(year)) {
        return 29;
    } else {
        return 28;
    }
}

// Function to check if a year is a leap year
int leapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

// Function to convert two dates into the number of days apart
int dateConvert(int year1, int year2, int month1, int month2, int day1, int day2){
    int days = 0;
    
    // Calculate the number of days in each year between year1 and year2
    for (int year = year1 + 1; year < year2; year++) {
        if (leapYear(year)) {
            days += 366;
        } else {
            days += 365;
        }
    }
    
    // Calculate the number of days in year1
    for (int month = month1; month < 12; month++) {
        days += daysInMonth(month, year1);
    }
    days += daysInMonth(month1, year1) - day1;
    
    // Calculate the number of days in year2
    for (int month = 1; month < month2; month++) {
        days += daysInMonth(month, year2);
    }
    days += day2;
    
    return days;
}

// Function to get user input 
int input(char *prompt, int min, int max){
    int buffer;
    int num;

    do{
        printf("Enter the %s (%d-%d): ", prompt, min, max);
        scanf("%d", &num);

        buffer = 0;

        while (getchar() != '\n'){
            buffer++;
        }
        
        if (buffer != 0){
            printf("Wrong input! Please enter the date in the given interval.\n");
        }   else if(num < min || num > max){
                printf("Incorrect number! Please enter a valid number in the intervals.\n");
            } 
    }while(buffer != 0 || num < min || num > max);
    
    return num;
}

int main() {
    DATE date1;
    DATE date2;
    int daysApart;

    // Get input for both dates, the first three cycles are then added to date 1 and the last three to date 2
    for (int i = 0; i < 6; i++){
        if (i == 0 || i == 3){
            date2.year = input("year", MIN, MAX);
            printf("You entered: %d\n", date2.year);
        }
        else if (i == 1 || i == 4){
            date2.month = input("month", 1, 12);
            printf("You entered: %d\n", date2.month);
        }
        else if (i == 2 || i == 5){
            date2.day = input("day", 1, daysInMonth(date2.month, date2.year));
            printf("You entered: %d\n", date2.day);
        }
        //Here the first three cycles go to date1
        if (i == 2){
            printf("The first date is: %d/%d/%d\n", date2.year, date2.month, date2.day);
            date1 = date2;
        }
    }
    printf("The first date is: %d/%d/%d\n", date1.year, date1.month, date1.day);
    printf("The second date is: %d/%d/%d\n", date2.year, date2.month, date2.day);

    // Call out the function to convert the dates into days
    daysApart = dateConvert(date1.year, date2.year, date1.month, date2.month, date1.day, date2.day);
    printf("These two dates are %d days apart from each other.\n", daysApart);
    return 0;
}