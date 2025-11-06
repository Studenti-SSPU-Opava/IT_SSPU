/*
 * beh.c ver. 1.0
 *
 * Otvírá soubor se závodníky, 
 * vypíše do souboru čas prvního 
 * a druhého kola.
 * =============================
 *
 * Radim Šenk - 30. 9. 2025
 * 
 */




//
// Nejlehci typ prikladu, doufejte v to... !!!JESTLI TOTO BUDETE KOPIROVAT TAK TENTO RADEK SMAZTE!!!
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DELIMS " :"
#define MAX_LINE_LENGTH 50
#define INPUT "zavodnici.txt"
#define OUTPUT "vysledky_olympiady.txt"

FILE *openFile(int fmode, const char *file, FILE *fileOpen);

typedef struct
{
    int min;
    float sec;
}ROUNDS_DATA;

typedef struct
{
    int startPosition;
    char surname[15];
    char firstname[15];
    ROUNDS_DATA firstRound;
    ROUNDS_DATA secRound;
}DATA;

DATA parseData(DATA data, char *storage){
    char *token;
    for (int i = 0; (token = (strtok(i == 0 ? storage : NULL, DELIMS))) != NULL; i++)
    {
        switch (i)
        {
        case 0:
            data.startPosition = atoi(token);
            break;
        case 1:
            strcpy(data.surname, token);
            break;
        case 2:
            strcpy(data.firstname, token);
            break;
        case 3:
            data.firstRound.min = atoi(token);
            break;
        case 4:
            data.firstRound.sec = atof(token);
            break;
        case 5:
            data.secRound.min = atoi(token);
            break;
        case 6:
            data.secRound.sec = atof(token);
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
    fr = openFile(1, INPUT, fr);
    return resized;
}

FILE *openFile(int fmode, const char *fileType, FILE *fileOpen){
    if (fmode == 0)
    {
        fileOpen = fopen(fileType, fileType == INPUT ? "r" : "w");
        if (fileOpen == NULL)
        {
            printf("Error encountered while trying to open the file %s.\n", fileType);
            exit(-101);
        }
        return fileOpen;
    } else if (fmode == 1)
    {
        if (!fclose(fileOpen))
        {
            printf("File %s successfully closed.\n", fileType);
        } else {
            printf("An error encountered while trying to close the file %s!\n", fileType);
            exit(-91);
        }
        return fileOpen;
    } else {
        exit (-192);
    }
}

void printOut(DATA *data, int total){
    printf("S T A R T O V N I  L I S T I N A - S L A L O M  Z E N Y\n"
        "----------------------------------------------------------------------\n"
        "startovni cislo |  prijmeni  |   jmeno   | cas 1. kola | cas 2. kola |\n"
        "----------------------------------------------------------------------\n");
    for (int i = 0; i < total; i++)
    {
        printf("       %2d | %15s | %15s |    %d:%05.2f |    %d:%05.2f |\n", data[i].startPosition, data[i].surname, data[i].firstname, data[i].firstRound.min,
            data[i].firstRound.sec, data[i].secRound.min, data[i].secRound.sec);
    }
}

float convertTime(ROUNDS_DATA firstR, ROUNDS_DATA secondR){
    return (float)(firstR.min + secondR.min) * 60 + (firstR.sec + secondR.sec);
}

void bubbleSort(DATA *data, int total){
    for (int i = 0; i < total - 1; i++)
    {
        int swapped = 0;
        for(int j = 0; j < total - 1 - i; j++){
            if (convertTime(data[j].firstRound, data[j].secRound) > convertTime(data[j + 1].firstRound, data[j + 1].secRound))
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

void formatTime(int totalTime, char *formated, int mode){
    int min =  totalTime / 6000;
    float sec = (totalTime % 6000);
    sprintf(formated, "%s%02d:%05.2f", mode == 1 ? "+" : "", min, sec / 100);
}

void fprintOut(DATA *data, int total){
    FILE *fw = openFile(0, OUTPUT, fw);
    char timeTotal[12];
    char lossOnV[12];

    fprintf(fw, "V Y S L E D K O V A  L I S T I N A\n"
        "---------------------------------------------------------------------------------\n"
        "poradi | cislo |    prijmeni     |      jmeno      | 1. kolo | 2. kolo |  celkem  |  ztrata   |\n"
        "---------------------------------------------------------------------------------\n");
    for (int i = 0; i < total; i++)
    {
        formatTime((int)(convertTime(data[i].firstRound, data[i].secRound) * 100), timeTotal, 0);
        formatTime((int)((convertTime(data[i].firstRound, data[i].secRound) - convertTime(data[0].firstRound, data[0].secRound)) * 100), lossOnV, 1);

        fprintf(fw, "   %02d |   %02d   | %15s | %15s | %d:%05.2f | %d:%05.2f | %s | %s |\n", i + 1, data[i].startPosition, data[i].surname, data[i].firstname,
            data[i].firstRound.min, data[i].firstRound.sec, data[i].secRound.min, data[i].secRound.sec, timeTotal, i == 0 ? "---------" : lossOnV);
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
