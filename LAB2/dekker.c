//INCLUDES
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


//Parent Process
int main(int argc, char *argv[]){

int turn = 1;
int i = 0, j = 1, k;
int flag[] = {1, 1};

do{

	
	printf("Entry Section initializing");
	
	flag[i] = 1;
	turn = j;

	for(k = 0; k<5; k++){

		printf(".");
		sleep(1);

	}
	printf("Setup complete!\n");

	while(flag[j] && turn == j){


	}

	flag[i] = 0;

	//remainder section

}while(1);

return (EXIT_SUCCESS);

}

