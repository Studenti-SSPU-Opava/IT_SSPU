/*
 * beh.c ver. 1.0
 *
 * Otvírá soubor se závodníky, 
 * spočítá pořadí závodníků,
 * vyfiltruje a vypíše závodníky z ČR.
 * ===================================
 *
 * Radim Šenk - 30. 9. 2025
 * 
 */
 


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define INPUT "beh.txt"
#define OUTPUT "vysledky.txt"
#define MAX_LINE_LENGTH 100
#define DATA_LENGTH 20
#define MAIN_DELIMS ";:"
#define SEC_DELIMS "."
// Exits --> -101 = fr error, -91 = fw error, -50 memory allocations errors... -999 parsing error...

FILE *fileOpen(FILE *fMode, int mode, const char *fileName);

typedef struct
{
    int hour;
    int min;
    int sec;
}TIME_FORMATED;

typedef struct
{
    int year;
    int month;
    int day;
}BIRTH_DATE;

typedef struct 
{
    int position;
    char surname[DATA_LENGTH];
    char firstname[DATA_LENGTH];
    char tempBirthDate[DATA_LENGTH];
    char nation[4];
    char team[DATA_LENGTH + DATA_LENGTH];
    TIME_FORMATED timeFormated;
    BIRTH_DATE birthdate;
}DATA;

DATA parseData(DATA data, char *storage){  
    char *token;
    for (int i = 0; (token = strtok(i == 0 ? storage : NULL, MAIN_DELIMS)) != NULL; i++)
    {
        switch (i)
        {
        case 0:
            data.position = atoi(token);
            break;
        case 1:
            strcpy(data.surname, token);
            break;
        case 2:
            strcpy(data.firstname, token);
            break;
        case 3:
            strcpy(data.tempBirthDate, token);
            break;
        case 4:
            strcpy(data.nation, token);
            break;
        case 5:
            strcpy(data.team, token);
            break;
        case 6:
            data.timeFormated.hour = atoi(token);
            break;
        case 7:
            data.timeFormated.min = atoi(token);
            break;
        case 8:
            data.timeFormated.sec = atoi(token);
            break;        
        default:
            exit(-999);
            break;
        }
    }
    char *bDayToken;
    for (int j = 0; (bDayToken = strtok(j == 0 ? data.tempBirthDate : NULL, SEC_DELIMS)) != NULL; j++)
    {
        switch (j)
        {
            case 0:
                data.birthdate.day = atoi(bDayToken);
                break;
            case 1:
                data.birthdate.month = atoi(bDayToken);
                break;
            case 2:
                data.birthdate.year = atoi(bDayToken);
                break;
            default:
                exit(-999);
                break;
        }
    }
    return data;
}

DATA *fillData(int *total){
    FILE *fr = fileOpen(fr, 0, INPUT);
    char storage[MAX_LINE_LENGTH];
    DATA *temp;
    DATA *resized;

    fgets(storage, MAX_LINE_LENGTH, fr);
    while (fgets(storage, MAX_LINE_LENGTH, fr) != NULL)
    {
        temp = (DATA *)realloc(resized, (*total + 1) * sizeof(DATA));
        resized = temp;
        
        if (resized == NULL)
        {
            exit(-50);
        }
        
        resized[*total] = parseData(resized[*total], storage);

        *total += 1;
    }

    fr = fileOpen(fr, 1, INPUT);
    return resized;
}

FILE *fileOpen(FILE *fMode, int mode, const char *fileName){
    if (mode == 0){
        fMode = fopen(fileName, fileName == INPUT ? "r" : "w");
        if (fMode == NULL)
        {
            exit(fileName == INPUT ? -101 : -91);
        }
    } else if (mode == 1)
    {
        if (!fclose(fMode))
        {
            printf("File %s closed successfuly.\n", fileName);
        } else {
            printf("Error encountered while tring to close the file %s.\n", fileName);
            exit(fileName == INPUT ? -101 : -91);
        }
    } else {
        exit(-101);
    }
    return fMode;
}

int getTime(){
    time_t seconds = time(NULL);
    struct tm *localTime = localtime(&seconds);
    return localTime->tm_year + 1900;
}

int findCzechs(DATA *data, int total){
    int czechs = 0;
    for (int i = 0; i < total; i++)
    {
        if (strcmp("CZE", data[i].nation) == 0)
        {
            czechs++;
        }
    }
    return czechs;
}

int compMonths(int firstMonth, int secondMonth){
    return firstMonth < secondMonth ? firstMonth : secondMonth;
}

int findTheOldest(DATA *data, int total){
    int index = 0;
    for (int i = 1; i < total; i++)
    {
        if (data[index].birthdate.year > data[i].birthdate.year)
        {
            index = i;
        } else if (data[index].birthdate.year == data[i].birthdate.year)
        {
            int sin = data[index].birthdate.month == compMonths(data[index].birthdate.month, data[i].birthdate.month);
            if (!sin)
            {
                index = i;
            }
        }
    }
    return index;
}

void printOut(DATA *data, int total){
    int index = findTheOldest(data, total);
    printf("S T A R T O V N I  L I S T I N A - M A R A T O N\n"
        "----------------------------------------------------------\n"
        "cislo |       prijmeni       |        jmeno         |  narozen  | stat |                   klub                   |   cas    |\n");
    for (int i = 0; i < total; i++)
    {
        printf(" %03d  | %20s | %20s |%02d.%02d.%04d |  %s | %40s | %02d:%02d:%02d |\n", data[i].position, data[i].surname, data[i].firstname,
            data[i].birthdate.day, data[i].birthdate.month, data[i].birthdate.year, data[i].nation, data[i].team,
            data[i].timeFormated.hour, data[i].timeFormated.min, data[i].timeFormated.sec);
    }
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Celkovy pocet zavodniku je %02d.\n", total);
    printf("Cechu je %d.\n", findCzechs(data, total));
    printf("Nejstarsim zavodnikem je %s %s narozen v roce %4d. Je mu %2d let.\n", data[index].surname, data[index].firstname,
        data[index].birthdate.year, getTime() - data[index].birthdate.year);
}

int convertTime(TIME_FORMATED timeForm){
    return timeForm.hour * 3600 + timeForm.min * 60 + timeForm.sec;
}

void bubbleSort(DATA *data, int total){
    for (int i = 0; i < total - 1; i++)
    {
        int swapped = 0;
        
        for (int j = 0; j < total - 1 - i; j++)
        {
            if (convertTime(data[j].timeFormated) > convertTime(data[j + 1].timeFormated))
            {
                DATA temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
                swapped++;
            }
        }
        if (swapped == 0)
        {
            break;
        }
    }
}

char *formatTheTime(int seconds, char *timefString){
    int hour = seconds / 3600;
    int min = (seconds % 3600) / 60;
    int sec = (seconds % 3600) % 60;
    sprintf(timefString, "+%02d:%02d:%02d", hour, min, sec);
}

void printToFile(DATA *data, int total){
    FILE *fw = fileOpen(fw, 0, OUTPUT);
    char timefString[12];
    
    fprintf(fw, "V Y S L E D K O V A  L I S T I N A - M A R A T O N\n"
        "---------------------------------------------------------------------------------------------------------------------------------------------------------------\n"
        "poradi | cislo |       prijmeni       |         jmeno        |  narozen   | stat |                    klub                  |   cas    |  ztrata   |\n"
        "---------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < total; i++)
    {
        formatTheTime(convertTime(data[i].timeFormated) - convertTime(data[0].timeFormated), timefString);
        fprintf(fw ,"   %02d  |  %03d  | %20s | %20s | %02d.%02d.%4d |  %s | %40s | %02d:%02d:%02d | %s |\n", i + 1, data[i].position, data[i].surname,
            data[i].firstname, data[i].birthdate.day, data[i].birthdate.month, data[i].birthdate.year, data[i].nation, data[i].team,
            data[i].timeFormated.hour, data[i].timeFormated.min, data[i].timeFormated.sec, i == 0 ? "         " : timefString);
    }
    fprintf(fw, 
        "---------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    fw = fileOpen(fw, 1, OUTPUT);
}

int main(){
    int total = 0;
    DATA *data = fillData(&total);
    printOut(data, total);
    bubbleSort(data, total);
    printToFile(data, total);

    free(data);
    printf("All done..\n");
    return 0;
}
//Hate thyself - copyright Šenk Radim - 30.9.2025