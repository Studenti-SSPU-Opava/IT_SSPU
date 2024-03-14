#include <stdio.h>

float balance = 0;  //set variables
float rate = 0;
float answer = 0;
float sum = 0;
int cycles = 0;

int inputCalc(const char *text, float number) {
    int charnum = 0;
    do
    {
        charnum = 0;
        printf("Input %d. account %s (positive number):\n", cycles, text);  //asks for number eighter for balance or interest rate, depends on const text
        scanf("%f", &number);
        while(getchar() != '\n'){   //check if buffer empty, else empty it and repeat the process for asking for number
            charnum++;
        } 
        if (charnum != 0 || number < 0) //if buffer was full, write message
        {
            printf("You inputed wrong number\n");
        }
    } while (charnum != 0 || number < 0);   //if buffer was full, repeat asking process
    return number;
}

float total(){  
    printf("Total sum of money is %f\n", sum);      //prints sum
    printf("Average worth of money on bank account is %f\n", (sum / cycles));   //prints average worth
}

float input(){
    cycles++;
    balance = inputCalc("balance", balance);    //asks for balance
    rate = inputCalc("interest rate", rate);    //asks for rate
    if (balance == 0 && rate == 0){             //if user entered both 0 on both numbers, end asking processes
        return -1;
    } 
    else {
    float output = balance + ((balance / 100) * rate);      //calculates new balance for the bank acc
    return output;
    }
    
}
int main() {
    do{
        answer = input();
        printf("Your new balance will be %f\n\n", answer);  //prints balance of one account
        sum = sum + answer;
    } while (answer != -1);
    cycles--;   //fix averaging problem (it thought there were 1 more bank acc)
    total();
    return 0;
}