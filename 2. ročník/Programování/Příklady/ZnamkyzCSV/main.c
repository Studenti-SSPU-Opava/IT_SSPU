#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENT_COUNT 5
#define INPUT "znamky.csv"
#define LINE_SIZE 100

typedef struct {
    char lastName[30];
    char firstName[30];
    int grades[5];
} STUDENTS;

int loadFile(STUDENTS* students) {
    char line[LINE_SIZE];
    int lineIndex = 0;

    FILE *file = fopen(INPUT, "r");
    if (file == NULL) {
        printf("Chyba při otevírání souboru %s.\n", INPUT);
        return 0;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        if (lineIndex != 0) {
            int colIndex = 0;
            char *pch = strtok(line, ", ");
            while (pch != NULL) {
                if (colIndex == 0) {
                    strcpy(students[lineIndex - 1].firstName, pch);
                } 
                else if (colIndex == 1) {
                    strcpy(students[lineIndex - 1].lastName, pch);
                } 
                else {
                    students[lineIndex - 1].grades[colIndex - 2] = atoi(pch);
                }
                pch = strtok(NULL, ", ");
                colIndex++;
            }
        }
    
        lineIndex++;
    }


    fclose(file);
    return lineIndex - 1;
}

void printStudents(STUDENTS* students, int studentCount) {
    for (int i = 0; i < studentCount; i++) {
        printf("%10s %10s: ", students[i].firstName, students[i].lastName);
        for (int j = 0; j < 5; j++) {
            printf("%3d ", students[i].grades[j]);
        }
        printf("\n");
    }
}



int main(void) {
    STUDENTS students[STUDENT_COUNT];
    int studentCount = 0;
    studentCount = loadFile(students);
    printStudents(students, studentCount);

    return 0;
}