#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int flag[2], i = 0, j = 1, turn;

void p1();
void p2();

//Parent Process
int main(int argc, char *argv[]){

	p1();
	p2();

	return 0;

}

void p1 (){

	char string[] = "P1";

	do
	{
		//Entry Section
		printf("%s is in the Entry Section\n", string);
		sleep(1);	
		flag[i] = 1;

		while(flag[j]){
			if (turn == j)
			{
				flag[i] = 0;
				while(turn == j);
				flag[i] = 1; 			
			}	
		}

		//Critical Section
		printf("%s is in the Critical Section. Please wait.....\n", string);
		sleep(5);	

		//Exit Section
		printf("%s is in the Exit Section\n", string);
		sleep(1);	

		turn = j;
		flag[i] = 0;

		//Remainder Section
		printf("%s is in the Remainder Section\n", string);
		sleep(1);	
		break;

	} while (1);

}

void p2 (){

	char string[] = "P2";

	do
	{
		//Entry Section
		printf("%s is in the Entry Section\n", string);
		sleep(1);	
		flag[j] = 1;

		while(flag[i]){
			if (turn == i)
			{
				flag[j] = 0;
				while(turn == i);
				flag[j] = 1; 			
			}	
		}

		//Critical Section
		printf("%s is in the Critical Section. Please wait.....\n", string);
		sleep(5);

		//Exit Section
		printf("%s is in the Exit Section\n", string);
		sleep(1);	

		turn = i;
		flag[j] = 0;

		//Remainder Section
		printf("%s is in the Remainder Section\n", string);
		sleep(1);	

		break;
	} while (1);

}