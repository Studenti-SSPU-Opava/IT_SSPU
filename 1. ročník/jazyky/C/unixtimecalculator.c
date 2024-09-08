#include <stdio.h>
#include <time.h>

int main() {
    // First date
    struct tm firstDate;
    printf("Enter the first date (YYYY-MM-DD HH:MM:SS): ");
    scanf("%d-%d-%d %d:%d:%d", &firstDate.tm_year, &firstDate.tm_mon, &firstDate.tm_mday, &firstDate.tm_hour, &firstDate.tm_min, &firstDate.tm_sec);
    firstDate.tm_year -= 1900; // Year - 1900
    firstDate.tm_mon -= 1; // Month (0-11)

    // Second date
    struct tm secondDate;
    printf("Enter the second date (YYYY-MM-DD HH:MM:SS): ");
    scanf("%d-%d-%d %d:%d:%d", &secondDate.tm_year, &secondDate.tm_mon, &secondDate.tm_mday, &secondDate.tm_hour, &secondDate.tm_min, &secondDate.tm_sec);
    secondDate.tm_year -= 1900; // Year - 1900
    secondDate.tm_mon -= 1; // Month (0-11)

    // Convert dates to Unix time
    time_t firstUnixTime = mktime(&firstDate);
    time_t secondUnixTime = mktime(&secondDate);

    // Calculate the difference in days
    double differenceInDays = difftime(secondUnixTime, firstUnixTime) / (60 * 60 * 24);

    printf("The difference in days is: %.0f\n", differenceInDays);

    return 0;
}
