#include<stdio.h>

int main()
{
	printf("Please give a positive number:\n");

	int num, remainder;

	/*Declaring Binary Base as constant=2.*/
	const int binBase = 2;

	/*Reading input (a positive number) from user*/
	scanf("%d", &num);

	/*In case user's input is wrong (<=0) we ask for input again
	  until he gives a right one.*/
	if(num<=0)
	{
		while(num<=0)
		{
			printf("Wrong input. The number must be positive, greater than 0. Please give number again:\n");
			scanf("%d", &num);
		}
	}

	printf("\nTraversed binary representation of number %d is:\n", num);

	/*Applying algorithm for transforming dec number to binary
      and printing each digit in every step.*/
	while(num>0)
	{
	    /*Ternary operator to check if the remainder is 1 or 0.*/
		remainder = ((num % binBase) ?1:0);
		printf("%d ", remainder);
		/*In every step current number becomes the result of current number/2.*/
		num = num/2;
	}
	printf("\n");

	return 0;
}
