#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    /*Declaring two file pointers on for input file and one for output file*/
	FILE *fp, *fpOutFile;
   	char buff[11];

   	/*Opening input file for reading. In case something goes wrong, exiting.*/
	if ((fp = fopen("bus.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    /*Reading a single line from the input file*/
    fscanf(fp,"%[^\n]", buff);
    /*Closing input file.*/
    fclose(fp);

    /*Acceptable format in input file is a single line with the 7 chars defining bus plate (3 chars and 4 numbers)
      followed by the number of seats. So the file must contain one line with 9 chars minimum and 10 max.
      In case we have wrong input, program can't continue and is exiting.*/
	if(strlen(buff)<9 || strlen(buff)>10){
		printf("Wrong file data. Fix it and run program again. Program is terminating.\n");
		exit(1);
	}

	char *seats;
	/*In case the input is 10 chars, the last two chars specify the number of seats.
	  In case its 9, the last char specifies the number of seats.*/
	if(strlen(buff) == 10) seats = &buff[strlen(buff) - 2];
	else seats = &buff[strlen(buff) - 1];

	/*We use atoi() to take the number of seats as integer.*/
	int numSeats = atoi(seats);

	/*Checking if number of seats follows format mentioned ---> 4*N+5*/
	int flag = 0, i=1;
	for(i=1; i<=12; i++){
		if(4*i+5 == numSeats) flag = 1;
	}
	if(flag == 0){
		printf("Wrong seats number. Seats number should follow format 4*N+5. Fix data in file and run program again. Program is terminating.\n");
		exit(1);
	}

	/*Using strtok() to split the input from file and take the bus plate without the number of seats.*/
	char *carPlate = strtok(buff, " ");
	printf("********************************************************************\n");
	printf("Data read from file ---> ");
	printf("Bus plate: %s --- ", carPlate);
	printf("Number of seats: %s\n", seats);
	printf("********************************************************************\n");


	/*Dynamic array to hold the seats. Size of the array is the number specified in the file.
      We are using malloc() for dynamic memory allocation as upon the start of execution we don't
      know the number of seats.*/
	int *seatsArray;
	seatsArray = (int *)malloc(sizeof(int)*numSeats);
	for(i=0; i < numSeats; i++) {
  		seatsArray[i] = 0;
	}

	int bookedWinCnt=0;

	/*Program should run until we give 0 as input. So ---> while(1)/*/
	while(1){
		/*Booking system menu provided to user*/
		printf("********************************************************************\n");
		printf("Bus booking system.\nPlease select an option:\n");
		printf("********************************************************************\n");
		printf("1. Print available seats and their numbers.\n");
		printf("2. Book an available seat by its number.\n");
		printf("3. Automatically book the first available seat next to a window.\n");
		printf("4. Cancel a booking by providing seat number.\n");
		printf("5. Check if a seat is already booked by providing its number.\n");
		printf("6. Print booked seats and their numbers.\n");
		printf("7. Print bus plate and the seat diagram.\n");
		printf("8. Save bus plate and seat diagram to file 'layout.txt'.\n");
		printf("0. Exit booking system.\n");
		printf("********************************************************************\n");

		/*Reading choice from user.*/
		int choice;
		scanf("%d", &choice);

		if(choice<0 || choice>8)
		{
			/*If user gives wrong input we ask him to give again. Because he can type wrong
			  input again we use this while loop to ask for input until he gives a right one. */
			while(choice<0 || choice>8){
				printf("Wrong input. Please type a number between 0 and 4.\n");
				scanf("%d", &choice);
			}
		}

		int seatChoice, winSeats;
		/*Number of seats next to windows.*/
		winSeats = (numSeats/4) * 2;

		/*Using switch with cases 0-8.*/
		switch(choice){
		    /*If we give 0, program is exiting.*/
			case 0 :
				printf("You typed '0'. Program is terminating.\n");
				exit(0);
            /*Printing list of available seats. A seat is not booked when it has value 0 in the array.*/
		  	case 1:
				printf("The list of available seats is:\n");
				for(i=0; i<numSeats; i++){
					if(seatsArray[i] == 0) printf("%d ", i+1);
				}
				printf("\n");
				break;
		  	case 2:
		    	printf("Please select a seat to book:\n");
				scanf("%d", &seatChoice);

				/*First check to see if user gave a valid seat number.*/
				if(seatChoice<1 || seatChoice>numSeats){
					printf("Wrong seat number. Please specify a seat between 1 and %d:\n", numSeats);
					scanf("%d", &seatChoice);
					while(seatChoice<1 || seatChoice>numSeats){
						printf("Wrong seat number. Please specify a seat between 1 and %d:\n", numSeats);
						scanf("%d", &seatChoice);
					}
				}
				/*Second check to see if seat selected is available.*/
				if(seatsArray[seatChoice-1] == 0) seatsArray[seatChoice-1] = 1;
				else{
					while(seatsArray[seatChoice-1] == 1){
						printf("Seat %d already booked. Please select another one.\n", seatChoice);
						scanf("%d", &seatChoice);
					}
				}
				seatsArray[seatChoice-1] = 1;
				printf("Seat %d successfully booked.\n", seatChoice);
		     	break;
		  	case 3:
				if(bookedWinCnt == winSeats){
					printf("There is no free seat next to window.\n");
					break;
				}
				else{
			        for(i=0; i<numSeats-4; i=i+4){
						if(seatsArray[i] == 0){
							seatsArray[i] = 1;
							bookedWinCnt++;
							printf("Successfully booked seat number %d.\n",i+1);
							break;
						}
						if(i+3 < numSeats){
							if(i+4 == numSeats-1){
								if(seatsArray[i+4] == 0){
									seatsArray[i+4] = 1;
									bookedWinCnt++;
									printf("Successfully booked seat number %d.\n", i+5);
									break;
								}
							}
							else{
								if(seatsArray[i+3] == 0){
									seatsArray[i+3] = 1;
									bookedWinCnt++;
									printf("Successfully booked seat number %d.\n",i+4);
									break;
								}
							}
						}
					}
				}
		        break;
		   	case 4:
	 			printf("Please select a seat to cancel a book:\n");
				scanf("%d", &seatChoice);

				/*First check to see if user gave a valid seat number.*/
				if(seatChoice<1 || seatChoice>numSeats){
					printf("Wrong seat number. Please specify a seat between 1 and %d:\n", numSeats);
					scanf("%d", &seatChoice);
					while(seatChoice<1 || seatChoice>numSeats){
						printf("Wrong seat number. Please specify a seat between 1 and %d:\n", numSeats);
						scanf("%d", &seatChoice);
					}
				}
				/*Second check to see if seat selected is booked.*/
				if(seatsArray[seatChoice-1] == 1) seatsArray[seatChoice-1] = 0;
				else{
					while(seatsArray[seatChoice-1] == 0){
						printf("Seat %d is free. Please select another one.\n", seatChoice);
						scanf("%d", &seatChoice);
					}
				}
				seatsArray[seatChoice-1] = 0;
				printf("Seat %d successfully cancelled.\n", seatChoice);
		        break;
			case 5:
				printf("Enter a seat between 1 and %d to see if its booked:\n", numSeats);
				scanf("%d", &seatChoice);
				if(seatChoice<1 || seatChoice>numSeats){
					printf("Wrong seat number. Please specify a seat between 1 and %d:\n", numSeats);
					scanf("%d", &seatChoice);
					while(seatChoice<1 || seatChoice>numSeats){
						printf("Wrong seat number. Please specify a seat between 1 and %d:\n", numSeats);
						scanf("%d", &seatChoice);
					}
				}
				if(seatsArray[seatChoice-1] == 0) printf("Seat number %d is available.\n", seatChoice);
				else printf("Seat number %d is already booked.\n", seatChoice);
				break;
			case 6:
				printf("The list of booked seats is:\n");
				for(i=0; i<numSeats; i++){
					if(seatsArray[i] == 1) printf("%d ", i+1);
				}
				printf("\n");
				break;
			case 7:
				printf("\n%s\n", carPlate);
				for(i=0; i<numSeats; i++){
                    /*If i%2 we should print a space (corridor) in case we are in any row except the last.*/
					if(i % 2 == 0 && i>0 && (i<numSeats-5)) printf(" ");
                    /*If i%4 changing row.*/
					if(i % 4 == 0 && i>0 && (i+1<numSeats)) printf("\n");
					if(seatsArray[i] == 0)printf("-");
					else printf("*");
				}
				printf("\n\n");
				break;
			case 8:
			    /*Opening output file for writing.*/
				if ((fpOutFile = fopen("layout.txt", "w")) == NULL)
    			{
        			printf("Error! opening file");
        			exit(1);
    			}

				fprintf(fpOutFile, "%s\n", carPlate);
				for(i=0; i<numSeats; i++){
					if(i % 2 == 0 && i>0 && (i<numSeats-5)) fprintf(fpOutFile, " ");
					if(i % 4 == 0 && i>0 && (i+1<numSeats)) fprintf(fpOutFile, "\n");
					if(seatsArray[i] == 0)fprintf(fpOutFile, "-");
					else fprintf(fpOutFile, "*");
				}

				printf("Successfully written bus plate and seat diagram to file 'layout.txt'.\n");
				fclose(fpOutFile);
				break;
		}
	}

	return 0;
}
