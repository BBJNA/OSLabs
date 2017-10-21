//INCLUDES
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

//Prototype functions
void Collatz(int num);

//Parent Process
int main(int argc, char* argv[]){

	int num = 0;
	pid_t pid = fork();


	if(pid < 0){

		printf("Child process was not created...Error Occurred");
		return (EXIT_FAILURE);
	
	}else if (pid == 0){

		//We were able to create a child process. Now we can run the Collatz Algorithm.
		while(num <= 0){

			printf("Enter in a number (n > 0): ");
			scanf("%d", &num);
		}

		printf("Collatz: ");
		Collatz(num);
		//printf("\nChild is completed...\n");

	}else{

		//We are in the parent process so we will wait until the child is done.
		//Child will send exit() allowing the parent to also reliquish.
		//printf("Waiting for child to finish....\n");
		wait(NULL);
		//printf("Parent can continue...\n");

	}

return (EXIT_SUCCESS);

}

void Collatz(int num){

	do{

		printf("%d ", num);

		if(num %2 == 0){

			num /= 2;

		}else{

			num = num*3+1;

		}

	}while(num > 1);

	printf("%d\n", num);

}