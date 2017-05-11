#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>



struct player {
 char name[21];
 char id;
 int score;
};

struct player players[4];

int Set[81][4];
int arrayDiktes[81];
int arrayPlay[12][4];


char display1(int i){
	if(i==0)return 'r';
	if(i==1)return 'g';
	if(i==2)return 'b';
}

char display2(int i){
	if(i==0)return 'c';
	if(i==1)return 't';
	if(i==2)return 'r';
}

char display3(int i){
	if(i==0)return 'b';
	if(i==1)return 'h';
	if(i==2)return 'e';
}

void display(){

	for( int i=0;i<81;i++){

		printf("%c %c %d %c",display1(Set[i][0]), display2(Set[i][1]),Set[i][2],display3(Set[i][3] ));

		printf("\n");
	}

}

void copyArray(){
	int step=0;
	for( int i=0;i<81;i++){
		if(arrayDiktes[i]==1){
			arrayPlay[step][0]=Set[i][0];
			arrayPlay[step][1]=Set[i][1];
			arrayPlay[step][2]=Set[i][2];
			arrayPlay[step][3]=Set[i][3];
			step++;
		}

	}

}

void displayPlay(){
	for( int i=0;i<12;i++){
			printf("[%c,%c,%d,%c]  ",display1(arrayPlay[i][0]), display2(arrayPlay[i][1]),arrayPlay[i][2],display3(arrayPlay[i][3] ));
			if(i%4==3)printf("\n");

	}

}

void initialize(){
	int step=0;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			for(int z=0;z<3;z++){
				for(int k=0;k<3;k++){
					Set[step][0]=i;
					Set[step][1]=j;
					Set[step][2]=z;
					Set[step][3]=k;
					step++;
				}
			}
		}
	}
}
void getNextCard(){
	for(int i=0;i<81;i++)arrayDiktes[i]=0;
	//Find 12 unique that i will use below
	int r = rand() % 81;
	arrayDiktes[r]=1;

	for(int i=0;i<11;i++){
		r = rand() % 81;
		while(arrayDiktes[r]==1){
			r = rand() % 81;
		}
		arrayDiktes[r]=1;
	}

	printf("#########################################\n");
	copyArray();
  	displayPlay();
}
int cart1,cart2,cart3;
int idPlayer;



int chekCarts(){
	int flagSum=0;
	if(arrayPlay[cart1][0]==arrayPlay[cart2][0] && arrayPlay[cart2][0]==arrayPlay[cart3][0] )flagSum +=1;
	if(arrayPlay[cart1][1]==arrayPlay[cart2][1] && arrayPlay[cart2][1]==arrayPlay[cart3][1] )flagSum +=1;
	if(arrayPlay[cart1][2]==arrayPlay[cart2][2] && arrayPlay[cart2][2]==arrayPlay[cart3][2] )flagSum +=1;
	if(arrayPlay[cart1][3]==arrayPlay[cart2][3] && arrayPlay[cart2][3]==arrayPlay[cart3][3] )flagSum +=1;

	if(arrayPlay[cart1][0]!=arrayPlay[cart2][0] && arrayPlay[cart2][0]!=arrayPlay[cart3][0] && arrayPlay[cart3][0]!=arrayPlay[cart1][0])flagSum +=1;
	if(arrayPlay[cart1][1]!=arrayPlay[cart2][1] && arrayPlay[cart2][1]!=arrayPlay[cart3][1] && arrayPlay[cart3][1]!=arrayPlay[cart1][1])flagSum +=1;
	if(arrayPlay[cart1][2]!=arrayPlay[cart2][2] && arrayPlay[cart2][2]!=arrayPlay[cart3][2] && arrayPlay[cart3][2]!=arrayPlay[cart1][2])flagSum +=1;
	if(arrayPlay[cart1][3]!=arrayPlay[cart2][3] && arrayPlay[cart2][3]!=arrayPlay[cart3][3] && arrayPlay[cart3][3]!=arrayPlay[cart1][3])flagSum +=1;

 	if(flagSum==4)return 1;

 	return 0;
}
int Best_Scor(){
	for(int cart1=1;cart1<12;cart1++){
		for(int cart2=1;cart2<12;cart2++){
			for(int cart3=1;cart3<12;cart3++){
				if(cart1==cart2)continue;
				if(cart2==cart3)continue;
				if(cart3==cart1)continue;
				int flagSum=0;
				if(arrayPlay[cart1][0]==arrayPlay[cart2][0] && arrayPlay[cart2][0]==arrayPlay[cart3][0] )flagSum +=1;
				if(arrayPlay[cart1][1]==arrayPlay[cart2][1] && arrayPlay[cart2][1]==arrayPlay[cart3][1] )flagSum +=1;
				if(arrayPlay[cart1][2]==arrayPlay[cart2][2] && arrayPlay[cart2][2]==arrayPlay[cart3][2] )flagSum +=1;
				if(arrayPlay[cart1][3]==arrayPlay[cart2][3] && arrayPlay[cart2][3]==arrayPlay[cart3][3] )flagSum +=1;

				if(arrayPlay[cart1][0]!=arrayPlay[cart2][0] && arrayPlay[cart2][0]!=arrayPlay[cart3][0] && arrayPlay[cart3][0]!=arrayPlay[cart1][0])flagSum +=1;
				if(arrayPlay[cart1][1]!=arrayPlay[cart2][1] && arrayPlay[cart2][1]!=arrayPlay[cart3][1] && arrayPlay[cart3][1]!=arrayPlay[cart1][1])flagSum +=1;
				if(arrayPlay[cart1][2]!=arrayPlay[cart2][2] && arrayPlay[cart2][2]!=arrayPlay[cart3][2] && arrayPlay[cart3][2]!=arrayPlay[cart1][2])flagSum +=1;
				if(arrayPlay[cart1][3]!=arrayPlay[cart2][3] && arrayPlay[cart2][3]!=arrayPlay[cart3][3] && arrayPlay[cart3][3]!=arrayPlay[cart1][3])flagSum +=1;

			 	if(flagSum==4){
			 		printf("\nThe correct are:\n");
			 		printf("%d\n",cart1+1);
			 		printf("%d\n",cart2+1);
			 		printf("%d\n",cart3+1);
			 		return 1;
			 	}
			}
		}
	}
	return 0;
}
void insertCard(){
	cart1=-1;
	cart2=-2;
	cart3=-3;

	printf("Give 3 times the correct couple of numbers:\n");
	printf(" 0-0    0-1   0-2   0-3\n");
	printf(" 1-0    1-1   1-2   1-3\n");
	printf(" 2-0    2-1   2-2   2-3\n");
	int flag=0;

	while(flag<3){
		char x[2],y[2];
		printf("Enter row:");
		scanf(" %s",x);
		printf("Enter column:");
		scanf("%s",y);

		if(strcmp(x,"-1") >0  && strcmp(x,"3")<0 && strcmp(y,"-1")>0 && strcmp(y,"4")<0){
			if(flag==0)cart1=atoi(x)*4+atoi(y);
			if(flag==1)cart2=atoi(x)*4+atoi(y);
			if(flag==2)cart3=atoi(x)*4+atoi(y);
			if(cart1!=cart2 && cart2!=cart3){
				printf("correct card\n");
				flag=flag+1;
			}
			else printf("you have given this card\n");
		}
		else{
			printf("Wrong input\n");
		}
	}
	printf("\n\n%d   %d    %d\n",cart1,cart2,cart3);

	if(chekCarts()==1){
		players[idPlayer].score +=2;
		system("cls");//cleaning screan
		printf("ok\n");
		printf("Your score: %d\n\n",players[idPlayer].score);

		if(players[idPlayer].score==10){
				printf("the player score = 10. o nikhths einai o %s. Program is terminating.\n",players[idPlayer].name);
				exit(0);
		}
		getNextCard();
		flag=0;
	}
	else{
		if(players[idPlayer].score>0)players[idPlayer].score -=1;

		system("cls");//cleaning screen
		printf("False\n");
		printf("Your score: %d\n",players[idPlayer].score);
		printf("Next in the same screen\n\n");
		displayPlay();
		cart1=-1;
		cart2=-2;
		cart3=-3;
		flag=0;
	}
	//system("pause");
}

void playerHelp(){//Search
	char lexi[20];
	int flag=0;
	while(flag==0 || players[idPlayer].score==10){
		printf("***********************************************************\n");
		printf("Please select option by typing the corresponding number:\n");
		printf("***********************************************************\n");
		printf("0. Exit program\n");
		printf("1. Insert cards\n");
		printf("2. Check solutions\n");
		printf("***********************************************************\n");
		scanf("%s",lexi);
		int flagBest=0;
		if(strcmp("0",lexi) == 0){
			system("cls");//cleaning screen
			flag=1;
		}
		else if(strcmp("1",lexi) == 0){
			insertCard();
		}
		else if(strcmp("2",lexi) == 0){
			if(Best_Scor()==0){
				printf("................................\n");
			}
		}

	}
}

//############################################################
int main(){
	//initializing

	players[0].id='a';
	strcpy(players[0].name, "Marina Andreou");
	players[0].score=0;

	players[1].id='g';
	strcpy(players[1].name, "Kostas Grammenos");
	players[1].score=0;

	players[2].id='p';
	strcpy(players[2].name, "Maria Perdika");
	players[2].score=0;

	initialize();

	srand(time(NULL));


	while(1){
			/*Initial menu provided to user*/
			printf("***********************************************************\n");
			printf("Please select option by typing the corresponding number:\n");
			printf("***********************************************************\n");
			printf("0. Exit program\n");
			printf("a. %s\n",players[0].name);
			printf("g. %s\n",players[1].name);
			printf("p. %s\n",players[2].name);
			printf("***********************************************************\n");

			char choice;
			scanf("%c", &choice);
			if(choice == '0'){
				system("cls");//cleaning screen
				printf("You typed '0'. Program is terminating.\n");
				exit(0);
			}
			else if(choice == 'a'){
				system("cls");//cleaning screen
				idPlayer=0;
				printf("Insert %s \n\n",players[idPlayer].name);
				getNextCard();
				playerHelp();
			}
			else if(choice == 'g'){
				system("cls");//cleaning screen
				idPlayer=1;
				printf("Insert %s \n\n",players[idPlayer].name);
				getNextCard();
				playerHelp();
			}
			else if(choice == 'p'){
				system("cls");//cleaning screen
				idPlayer=2;
				printf("Insert %s \n\n",players[idPlayer].name);
				getNextCard();
				playerHelp();
			}
			else{
				system("cls");//cleaning screen
			}

	}

}

