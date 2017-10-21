//INCLUDES
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>


//Parent Process
int main(int argc, char *argv[]){

	int numinputs, i = 0;

	printf("Number of inputs: ");
	scanf("%d", &numinputs);

	int numbers[numinputs];

	printf("Enter in Numbers (Press enter for new entry):\n");

	while(i<numinputs){

		scanf("%d", &numbers[i]);
		i++;

	}

	i = 0;

return (EXIT_SUCCESS);

}

