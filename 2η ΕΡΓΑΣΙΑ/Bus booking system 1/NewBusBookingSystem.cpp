//BusBookingSystem

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bus_system {
 char data[41];
 char phone[11]; //unsigned  short
 unsigned int number;
};

#define n 53
struct bus_system Bus[n];
char *seats;
char carPlate[8];
int numSeats;
char FirstLine[11];


void display(struct bus_system Bus[]){  // Display function on the screen
     printf("\n\nAA.  number   phone                           data\n");
     printf("-------------------------------------------------------------\n");
    for(int i=0; i<53;i++){
    	if(Bus[i].number==-1)continue;
    	printf("%d %4d %10s %40s\n",i+1, Bus[i].number,Bus[i].phone ,Bus[i].data);
    }

    printf("\n");

     }


void Splitting(char grammi[80]){
	char * pch;
	int step=1;
	char *str1,*str2,*str3,*str4;
	pch = strtok (grammi," ,\n");
	while (pch != NULL)
	{   if(step==1)str1=pch;
		if(step==2)str2=pch;
		if(step==3)str3=pch;
		if(step==4)str4=pch;

	    pch = strtok (NULL, " ,\n");
	    step +=1;
	}

	char str[41];
  	strcpy (str,str1);
  	strcat (str," ");
  	strcat (str,str2);

  	int id=atoi(str3)-1;

	Bus[id].number=id+1;
	strcpy(Bus[id].phone,str4);
	strcpy(Bus[id].data,str);


}

#define LIM 100     //number of lines entered
void InsertFile(){     //we enter the whole line
  FILE *fp;
    char grammi[80];
    int line=0;


	fp=fopen("bus.txt","r");
    if (fp==NULL) exit(0);
    while(!feof(fp))
    {	strcpy(grammi,"");
	    fgets(grammi,80,fp);
	    if(line==0){
	    	strcpy(FirstLine,grammi);

	    	char * pch;
			int step=1;
			char *str11,*str12;
			pch = strtok (grammi," ,\n");
			while (pch != NULL)
			{   if(step==1)str11=pch;
				if(step==2)str12=pch;

			    pch = strtok (NULL, " ,\n");
			    step +=1;
			}

			strcpy(carPlate,str11);
	    	numSeats = atoi(str12);

	    	line +=1;

	    	continue;
	    }

	    if(strcmp("",grammi)==0)break;
	    Splitting(grammi);
    }

    fclose(fp);
}

void syn_1(){
	printf("The free seats are:\n");
	int step=0;
	for(int i=0; i<53;i++){
    	if(Bus[i].number!=-1)continue;
    	printf("%d - ",i+1);
    	step +=1;
    	if(step%15==14)printf("\n");
    }
    printf("\n");
}

void writeTxt(){
	FILE *fp;
   fp = fopen("bus.txt", "w");
   fprintf(fp, FirstLine);//writes the first line....

   for(int i=0; i<53;i++){
    	if(Bus[i].number==-1)continue;
    	char line[100];
    	strcpy(line,Bus[i].data);
    	strcat(line, " ");

		char str[10];
		int convert=Bus[i].number;
		sprintf( str, "%d", convert ); //converts integer to char
		strcat(line,str);

    	strcat(line, " ");
    	strcat(line,Bus[i].phone);
    	strcat(line,"\n");
    	fprintf(fp, line);
    }

   fclose(fp);
}

void syn_2(){
	syn_1();
	char lexi[20];
			int flag=0;
			int idBus;
			while(flag==0){
					printf("Please type a number between 1 and 53 and free...........\n");
					scanf("%s",lexi);

					int ret1,ret2;
					ret1=strcmp("0",lexi);
					ret2=strcmp("54",lexi);

					if(ret1<0 && ret2>0){//checking if it's in the zone
						flag=1;
					}
					if(flag==1){//checking if it's free
						flag=0;
						idBus=atoi(lexi)-1;
						if(Bus[idBus].number==-1)flag=1;
					}
			}
			flag=0;
			while(flag==0){
				printf("***********************************************************\n");
				printf("Please select choice by typing the corresponding number:\n");
				printf("***********************************************************\n");
				printf("0. Exit program\n");
				printf("1. Insert data\n");
				printf("***********************************************************\n");
				scanf("%s",lexi);
				if(strcmp("0",lexi) == 0){
					system("cls");//cleaning screen
					flag=1;
				}
				else{
					system("cls");//cleaning screen

					char LastName[41];
					char FirstName[41];
					char Phone[11];
					while(flag==0){
						printf("Insert LastName:\n");
						scanf("%s",&LastName);
						printf("Insert FirstName:\n");
						scanf("%s",&FirstName);

						printf("Insert Phone:\n");
						scanf("%s",&Phone);

						int a=strlen(LastName);
						int b=strlen(FirstName);
						int c=strlen(Phone);
						if(a+b<41 && c==10){
							Bus[idBus].number=idBus+1;
							strcat(LastName, " ");
							strcat(LastName, FirstName);
							strcpy(Bus[idBus].data, LastName);
							strcpy(Bus[idBus].phone,Phone);
							flag=1;
						}
						else{
							system("cls");//cleaning screen
							printf("Max Len>40\n");
						}
					}
					writeTxt();
					printf("Registration ok\n");
					display(Bus);
					flag=1;
				}
			}


}

void syn_3(){//Search
	char lexi[20];
	int flag=0;
	while(flag==0){
			printf("***********************************************************\n");
				printf("Please select choice by typing the corresponding number:\n");
				printf("***********************************************************\n");
				printf("0. Exit program\n");
				printf("1. Search data\n");
				printf("2. Search phone\n");
				printf("***********************************************************\n");
				scanf("%s",lexi);
				int flagBest=0;
				if(strcmp("0",lexi) == 0){
					system("cls");//cleaning screen
					flag=1;
				}
				else if(strcmp("1",lexi) == 0){
					system("cls");//cleaning screen
					char LastName[41];
					char FirstName[41];
					while(flag==0){
						printf("Insert LastName:\n");
						scanf("%s",&LastName);
						printf("Insert FirstName:\n");
						scanf("%s",&FirstName);
						strcat(LastName, " ");
						strcat(LastName, FirstName);
						for(int i=0; i<53;i++){
							if(strcmp(LastName,Bus[i].data) == 0){
								printf("Has reserved seat %d \n",Bus[i].number);
								flagBest=1;
							}
						}
						flag=1;
					}
					if(flagBest==0){
						printf("Such reservation does not exist\n");
					}
				}
				else if(strcmp("2",lexi) == 0){
					flagBest=0;
					flag=0;
					system("cls");//cleaning screen
					char Phone[11];
					while(flag==0){
						printf("Insert Phone:\n");
						scanf("%s",&Phone);
						for(int i=0; i<53;i++){
							if(strcmp(Phone,Bus[i].phone) == 0){
								printf(" %s has reserved seat  %d \n",Bus[i].data,Bus[i].number);
								flagBest=1;
							}
						}
						flag=1;
					}
					if(flagBest==0){
						printf("Such reservation does not exist\n");
					}

				}
	}
}

void syn_4(){

	printf("Reserved seats\n");
	int step=0;
	for(int i=0; i<53;i++){
    	if(Bus[i].number!=-1){
	    	printf("%d - ",i+1);
	    	step +=1;
		}
    	if(step%15==14)printf("\n");
    }
    printf("\n");

	int seatsDelete;
	printf("Insert seats to Delete:\n");
	scanf("%d",&seatsDelete);
	seatsDelete=seatsDelete-1;
	strcpy( Bus[seatsDelete].data, "");
	strcpy(Bus[seatsDelete].phone,"");
	Bus[seatsDelete].number=-1;
	writeTxt();
	printf("Delete ok\n");
	display(Bus);
}
//#################################################################
int main()
{

	//initializing array
	for(int i=0;i<53;i++){
		strcpy( Bus[i].data, "");
		strcpy(Bus[i].phone,"");
		Bus[i].number=-1;
	}

	InsertFile();


		while(1){
				/*Initial menu provided to user*/
			printf("***********************************************************\n");
			printf("Please select choice by typing the corresponding number:\n");
			printf("***********************************************************\n");
			printf("0. Exit program\n");
			printf("1. Number of empty seats and presentation\n");
			printf("2. Insert seats\n");
			printf("3. Search\n");
			printf("4. Delete\n");
			printf("5. Display\n");
			printf("***********************************************************\n");

			int choice;
			scanf("%d", &choice);

			if(choice<0 || choice>5)
			{
					/*If user gives wrong input we ask him to give again. Because he can type wrong
			  	input again we use this while loop to ask for input until he gives a right one. */
				while(choice<0 || choice>5){
					printf("Wrong input. Please type a number between 0 and 5.\n");
					scanf("%lf", &choice);
				}
			}
			if(choice == 0){
				system("cls");//cleaning screen
				printf("You typed '0'. Program is terminating.\n");
				exit(0);
			}
			else if(choice == 1){
				system("cls");//cleaning screen
				syn_1();

			}
			else if(choice == 2){
				system("cls");//cleaning screen
				syn_2();
			}
			else if(choice == 3){
				system("cls");//cleaning screen
				syn_3();
			}
			else if(choice == 4){
				system("cls");//cleaning screen
				syn_4();
			}
			else if(choice == 5){
				system("cls");//cleaning screen
				display(Bus);
			}

		}
system("pause");

return 0;
}

