/*
 * beh.c ver. 1.0
 *
 * Otvírá soubor se závodníky, 
 * vypíše do souboru pořadí a ztrátu 
 * na vedoucího závodníka.
 * =================================
 *
 * Radim Šenk - 30. 9. 2025
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DELIMS " :,"
#define MAX_LINE_LENGTH 50
#define INPUT "startovni_listina_kombinace_zeny.txt"
#define OUTPUT "vysledky_kombinace_zeny.txt"

// Exits --> -101 = fr error, -91 = fw error, -50 memory allocations errors... -999 parsing error...

typedef struct
{
    int min;
    int sec;
    int centisec;
}FIRST_TIME;

typedef struct
{
    int seconds;
    int centisec;
}SECOND_TIME;

typedef struct
{
    int position;
    char firstname[20];
    char surname[20];
    char nation[4];
    FIRST_TIME firstTime;
    SECOND_TIME secondTime;
}DATA;

FILE *openFile(int foMode, const char *file, FILE *fr);

DATA parseData(DATA data, char *storage){
    char *token;
    for (int i = 0; (token = strtok(i == 0 ? storage : NULL, DELIMS)) != NULL; i++)
    {
        switch (i)
        {
        case 0:
            data.position = atoi(token);
            break;
        case 1:
            strcpy(data.firstname, token);
            break;
        case 2:
            strcpy(data.surname, token);
            break;
        case 3:
            strcpy(data.nation, token);
            break;
        case 4:
            data.firstTime.min = atoi(token);
            break;
        case 5:
            data.firstTime.sec = atoi(token);
            break;
        case 6:
            data.firstTime.centisec = atoi(token);
            break;
        case 7:
            data.secondTime.seconds = atoi(token);
            break;
        case 8:
            data.secondTime.centisec = atoi(token);
            break;
        default:
            exit(-999);
            break;
        }
    }
    return data;
}

DATA *fillData(int *total){
    FILE *fr = openFile(0, INPUT, fr);
    DATA *temp, *resized;
    char storage[MAX_LINE_LENGTH];

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
    fr = openFile(1, INPUT, fr);
    return resized;
}

FILE *openFile(int foMode, const char *file, FILE *fName){
    
    if (foMode == 0)
    {
        fName = fopen(file, file == INPUT ? "r" : "w");
        if (fName == NULL)
        {
            printf("Error encountere while tring to close the file %s!\n", file);
            exit(file == INPUT ? -101 : -91);
        }
        return fName;
    } else if (foMode == 1)
    {
        if (!(fclose(fName)))
        {
            printf("File %s closed successfully.\n", file);
        }
        else {
            printf("Error encountered while tring to close the file %s!\n", file);
            exit(file == INPUT ? -101 : - 91);
        }
        return fName;    
    } else {
        exit(-192);
    }
}

void printOut(DATA *data, int total){
    printf("Alpske lyzovani startovni listina K O M B I N A C E  Z E N Y\n"
        "------------------------------------------------------------------------------------\n"
        "startovni cislo                 jmeno               prijmeni  stat   sjezd  slalom\n"
        "------------------------------------------------------------------------------------\n"
    );
    for (int i = 0; i < total; i++)
    {
        printf("             %02d  %20s   %20s   %s  %d:%02d,%02d  %2d,%02d\n", data[i].position, data[i].firstname,
            data[i].surname, data[i].nation, data[i].firstTime.min, data[i].firstTime.sec, data[i].firstTime.centisec,
            data[i].secondTime.seconds, data[i].secondTime.centisec);
    }
}

int convertTime(FIRST_TIME ft, SECOND_TIME st){
    // min to sec is "min * 60", sec to centisec is "sec * 100". As such mins to centisec is "min * 6000"
    return ft.min * 6000 + (ft.sec + st.seconds) * 100 + (ft.centisec + st.centisec); 
}

void bubbleSort(DATA *data, int total){
    for (int i = 0; i < total - 1; i++)
    {
        int swapped = 0;
        for (int j = 0; j < total - 1 - i; j++)
        {
            if (convertTime(data[j].firstTime, data[j].secondTime) > convertTime(data[j + 1].firstTime, data[j + 1].secondTime))
            {
                DATA temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
                swapped++;
            }            
        }
        if (swapped == 0){
            break;
        }
    }
}

void *formattedTime(int totalTime, char *formStr){
    int min = totalTime / 6000;
    int sec = (totalTime % 6000) / 100;
    int centisec = (totalTime % 6000) % 100;

    sprintf(formStr, "%d:%02d,%02d", min, sec, centisec);
}

void fprintOut(DATA *data, int total){
    char finishTimes[10];
    char lossOnVTimes[10];
    FILE *fw = openFile(0, OUTPUT, fw);

    fprintf(fw, "A L P S K E  L Y Z O V A N I - K O M B I N A C E  Z E N Y\n"
        "--------------------------------------------------------------------------------------------------------------\n"
        "poradi              jmeno            prijmeni stat   sjezd   slalom   celkem    ztrata\n"
        "--------------------------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < total; i++)
    {
        formattedTime(convertTime(data[i].firstTime, data[i].secondTime), finishTimes);
        formattedTime(convertTime(data[i].firstTime, data[i].secondTime) - convertTime(data[0].firstTime, data[0].secondTime), lossOnVTimes);
        fprintf(fw, "  %02d.%20s%20s  %s  %d:%02d,%02d  %2d,%02d   %s   %s\n", i + 1, data[i].firstname, data[i].surname, data[i].nation,
            data[i].firstTime.min, data[i].firstTime.sec, data[i].firstTime.centisec, data[i].secondTime.seconds, data[i].secondTime.centisec, finishTimes,
            i == 0 ? "-------" : lossOnVTimes);
    }
    
    fw = openFile(1, OUTPUT, fw);
}

int main(){
    int total = 0;
    DATA *data = fillData(&total);
    printOut(data, total);
    bubbleSort(data, total);
    fprintOut(data, total);

    free(data);
    printf("All done..\n");
    return 0;
}