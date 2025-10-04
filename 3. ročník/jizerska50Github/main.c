#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 100
#define DELIMS ";,():"
#define INPUT "jizerska50.txt"
#define OUTPUT "vysledkova_listina.txt"

typedef struct
{
    int hour;
    int min;
    int sec;
}FINISH_TIME;


typedef struct
{
    int position;
    char surname[20];
    char firstname[20];
    int year;
    char nation[4];
    FINISH_TIME ft;
}DATA;

FILE *openFile(int fmode, char *fileName, FILE *file);

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
            strcpy(data.surname, token);
            break;
        case 2:
            strcpy(data.firstname, token);
            break;
        case 3:
            data.year = atoi(token);           
            break;
        case 4:
            strcpy(data.nation, token);
            break;
        case 5:
            data.ft.hour = atoi(token);
            break;
        case 6:
            data.ft.min = atoi(token); 
            break;
        case 7:
            data.ft.sec = atoi(token);            
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
    char storage[MAX_LINE_LENGTH];
    DATA *temp, *resized;
    
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

FILE *openFile(int fmode, char *fileName, FILE *file){
    if (fmode == 0)
    {
        file = fopen(fileName, fileName == INPUT ? "r" : "w");
        if (file == NULL)
        {
            printf("Error encountered while trying to open file %s.\n", fileName);
            exit(-101);
        }
        return file;
    } else if (fmode == 1)
    {
        if (!fclose(file))
        {
            printf("File %s closed successfuly.\n", fileName);
        } else {
            exit(-91);
        }
        return file;
    } else {
        exit(-191);
    }
}

void printOut(DATA *data, int total){
    

    printf("S T A R T O V N I  L I S T I N A - J I Z E R S K A 50\n\n"
            "startovni cislo     prijmeni        jmeno  rocnik  stat\n\n");
    for (int i = 0; i < total; i++)
    {
        printf("%d   %s  %s  %d  %s  %02d:%02d:%02d\n",
            data[i].position, data[i].surname, data[i].firstname, data[i].year, data[i].nation,
            data[i].ft.hour, data[i].ft.min, data[i].ft.sec);
    }

}

int main(){
    int total = 0;
    DATA *data = fillData(&total);
    printOut(data, total);


    free(data);
    printf("All done..\n");
    return 0;
}