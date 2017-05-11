#include <stdio.h>
#include <stdlib.h>

int main()
{
    float num1, num2;
    char operation;

    printf("Give two numbers and the symbol of the operation:\n");
    /*Reading from user first number, symbol of the desired operation (+, -, *, /) and second number.*/
    scanf("%f%c%f", &num1, &operation, &num2);

    /*Checking operation symbol and printing the corresponding result*/
    if (operation == '+') printf("%f\n", num1+num2);
    else if (operation == '-') printf("%f\n", num1-num2);
    else if (operation == '*') printf("%f\n", num1*num2);
    else if (operation == '/')
    {
        /*Checking if divisor is zero or not*/
        if( num2!= 0) printf("%f\n", num1/num2);
        else if (num2==0) printf("We can't divide by 0.\n");
    }
    /*In case operation symbol is different than +, -, *, /, program is terminating with
    a wrong input message. */
    else printf("Wrong input.\n");

    return 0;
}

