#include <stdio.h>
#include <stdlib.h>

void pointersExperiment()
{
    int number = 10;
    int *pointer = &number;
    printf("This is the address of the number: %p\n"
           "This is the value of the number: %d\n",
           pointer, *pointer);
    int array[5] = {10, 20, 30, 40, 50};
    printf("This is a failure executed successfully: %d\n"
           "This is the way: %d\n",
           *array + 1, *(array + 1));
}

int main()
{
    int *pointer = NULL;
    int desiredLength;
    printf("How long do you want the array to be?\n Enter: ");
    scanf("%d", &desiredLength);
    pointer = (int *)malloc(desiredLength * sizeof(int));
    if (pointer == NULL)
    {
        printf("Bad pointer\n");
        return 1;
    }
    srand(time(NULL));

    printf("Memory allocation was successful\n");
    for (int i = 0; i < desiredLength; i++)
    {
        pointer[i] = rand() % 1000 + 1;
        printf("The address of the array position %d is: %p\n"
               "Its value is: %d\n",
               i, &pointer[i], pointer[i]);
        if (pointer[i] == 1000)
        {
            printf("------------------------------------------------------------------------------------------------------------------\n"
                   "--------------------------------------JACKPOOOOOOOOTTTTTTTT-------------------------------------------------------\n"
                   "------------------------------------------------------------------------------------------------------------------\n");
        }
    }

    free(pointer);
    return 0;
}