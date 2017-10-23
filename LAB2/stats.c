#define _GNU_SOURCE
#include <signal.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sched.h>
#include <malloc.h>
#include <pthread.h>


#define STACK 1024*1024

int Average(void *numbers){

	double avg,sum=0;
	int i=1;

	while(i<((int *)numbers)[0]){

		sum += ((int *)numbers)[i];
		i++;
	}

	avg = sum/((int *)numbers)[0];

	printf("Average Value: %lf\n", avg);

	return 0;
}

int Min(void *numbers){

	double min = ((int *)numbers)[0];
	int i=1;

	while(i<((int *)numbers)[0]){

		if (min>((int *)numbers)[i])
		{
			min = ((int *)numbers)[i];
		}
		i++;
	}

	printf("Minimum Value: %lf\n", min);

	return 0;
}

int Max(void *numbers){

	double max = ((int *)numbers)[0];
	int i=1;


	while(i<((int *)numbers)[0]){

		if (max<((int *)numbers)[i])
		{
			max = ((int *)numbers)[i];
		}
		i++;
	}

	printf("Maximum: %lf\n", max);

	return 0;
}

//Parent Process
int main(int argc, char *argv[]){

	int numinputs, i = 1;

	printf("Number of inputs: ");
	scanf("%d", &numinputs);

	int numbers[numinputs+1];
	numbers[0] = numinputs;

	printf("Enter in Numbers (Press enter for new entry):\n");

	while(i<numinputs+1){

		scanf("%d", &numbers[i]);
		i++;

	}

	char *stack = (char *)	malloc(STACK);

	if(stack == 0){

		perror("malloc failed...");
		exit(1);

	}

	char *stackhead = stack + STACK -1;

	pid_t pidAvg, pidMin, pidMax;

	pidAvg = clone(Average,stackhead,CLONE_VM | CLONE_FS| 
		CLONE_FILES | CLONE_SIGHAND | CLONE_THREAD | CLONE_SETTLS | 
		CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | CLONE_SYSVSEM | 
		CLONE_DETACHED, numbers);

	pidMax = clone(Max,stackhead,CLONE_VM | CLONE_FS| 
		CLONE_FILES | CLONE_SIGHAND | CLONE_THREAD | CLONE_SETTLS | 
		CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | CLONE_SYSVSEM | 
		CLONE_DETACHED, numbers);

	pidMin = clone(Min,stackhead,CLONE_VM | CLONE_FS| 
		CLONE_FILES | CLONE_SIGHAND | CLONE_THREAD | CLONE_SETTLS | 
		CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | CLONE_SYSVSEM | 
		CLONE_DETACHED, numbers);

	waitpid(-1, NULL, __WALL);
	if (pidAvg == -1)
	{	
		perror("waitpid");
		exit(3);
	}

	free(stack);

return (EXIT_SUCCESS);

}

