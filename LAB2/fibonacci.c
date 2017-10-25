#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define size 25

int fibonacci_arr[size]; /* data shared by the thread(s) */
void *fibonacci(void *param); /* threads call this function */

int main(int argc, char *argv[]) {
	pthread_t tid;	/* the thread identifier */
	pthread_attr_t attr;	/* set of thread attributes */
	int x;
	int num = atoi(argv[1]); /* Convert string value to integer */


	/* tell user to give non-negitive number if one was given */
	if(atoi(argv[1]) < 0) {	
		fprintf(stderr, "%d must be >= 0\n", atoi(argv[1]));
		return -1;
	} 

	/* non-negitive number was inputed create threads */
	else { 

	/* get the default attributes */
	pthread_attr_init(&attr);

	/* create the thread */
	pthread_create(&tid, &attr, fibonacci, argv[1]);

	/* wait for the thread to exit */
	pthread_join(tid, NULL);

	}

	/* print out the sequence generated */
	for(x = 0; x < num; x++) {
		printf("%d ", fibonacci_arr[x]);
	}

	printf("\n");

	return 0;
}

/* The thread will begin control in this function */
void *fibonacci(void *param) {
	int i;
	int x = 0;
	int y = 1;
	int fibn = 0;
	int upper = atoi(param); 

	/* Fibonacci Formula */
	for(i = 1; i <= upper; i++) {
		fibonacci_arr[i - 1] = fibn;
		fibn = x + y;
		x = y;
		y = fibn;
	}

	pthread_exit(0);
}
/* Terminal Commands */
/* gcc -pthread -o fibonacci fibonacci.c */
/* ./fibonacci #(any number user wants) */

