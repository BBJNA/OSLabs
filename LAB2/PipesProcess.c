#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>

/*
// some macros to make the code more undertandable
// regarding which pipe to use to a read.write operation
//
// Parent: reads from P1_READ, writes on P1_WRITE
// Child: reads from P2_READ, writes on P2_WRITE
*/

#define P1_READ 0
#define P2_WRITE 1
#define P2_READ 2
#define P1_WRITE 3

// the total number of pipes *pairs* we need
#define NUM_PIPES 2


char *toggleString(char *argv) {
	int i;	/* Declare counter */

	char *str = malloc(sizeof(argv[1])); 	/* Declare array sizeof input */

	strcpy(str, argv);	/* Copy String to char array */

	for(i = 0; str[i] != '\0'; i++) {	// Loop through length of string
		if(str[i] >= 'A' && str[i] <= 'Z') {	//if the array at i is uppercase
			str[i] += 32;	// Make it lower case
		}
		else if(str[i] >= 'a' && str[i] <= 'z') { 	// if the array at i is lowercase
			str[i] -= 32;	// Make it uppercase
		}
	}
	return str;
}

int inputValidation(int argc, char *argv[]) {
	int i;	// Declare counter variable

	bool c = false;	// Declare boolean flag using imported <stdbool.h>

	char str[strlen(argv[1])];	// Declare str

	strcpy(str, argv[1]);	// Copy argument into str

	if(argc != 2) {		// check to see if we have enough arguments to continue
		// Prompt user of correct usage
		fprintf(stderr, "\nUsage: %s <string> or <'string 1, string 2', ..., stringn'> for multiple strings\n",
			argv[0]);
		exit(EXIT_FAILURE);	// Exit on improper input
	} else {
		// loop through our string
		for(i = 0; i < strlen(str); i++) {
			// if any char is a reversible character
			if(isalpha((int) str[i])) {
				c = true;	// set the flag to true
			}
		}
		if(c == false) {	// If flag is false input does not contain any reversible characters
			printf("\nSorry, The string you entered did NOT contain any Alphabetical Characters\nRun me again, with at least 1 Alphabetical character\n\n");
			exit(EXIT_FAILURE);		// Exit on improper input
		}
		return (0);
	}
}

int main(int argc, char *argv[]) {
	assert(argc > 1);

	int fd[2*NUM_PIPES];	// Declare int[] of file descriptors

	int len, i;		// Declare length and integer for count

	pid_t pid;		// Declare process id

	char parent[strlen(argv[1])]; 	// Declare Parent array

	char child[strlen(argv[1])]; 	// Decalare Child array

	if(inputValidation(argc, argv) == 0) /* Check for proper input */
	strcpy(parent, argv[1]);

	// create all the descriptor pairs we need
	for(i = 0; i < NUM_PIPES; i++) {
		if(pipe(fd + (i*2)) < 0) {
			perror("Failed to allocate pipes");
			exit(EXIT_FAILURE);
		}
	}
	// fork() returns 0 for child process, child-pid for parent process
	if((pid = fork()) < 0) {
		perror("Failed to for process");
		return EXIT_FAILURE;
	}
	// Child Code Begins //
	// if the pid is zero, this is the child process
	if(pid == 0) {
		// Child. Start by closing descriptors we dont need in this process
		close(fd[P1_READ]);
		close(fd[P1_WRITE]);

		// used for output
		pid = getpid();

		// wait for parent to send us a value
		len = read(fd[P2_READ], &child, len);
		if(len < 0) {
			perror("Child: Failed to read data from pipe");
			exit(EXIT_FAILURE);
		}
		else if(len == 0) {
			// not an error, but certainly unexpected
			fprintf(stderr, "Child: Read EOF from pipe");
		} else {
			// report pid to consol
			printf("Child(%d): Recieved Message\n\nChild(%d): Toggling Case and Sending to Parent\n", pid, pid);

			// send the message to toggleString and write it to pipe
			if(write(fd[P2_WRITE], toggleString(child), strlen(child)) < 0) {
				perror("Child: Failed to write response value");
				exit(EXIT_FAILURE);
			}
		}
		// finished, Close remaining descriptors.
		close(fd[P2_READ]);
		close(fd[P2_WRITE]);

		return EXIT_SUCCESS;
	}
	// Child Code Ends //
	// Parent Code Begins //
	// Parent. Close unneeded descriptors
	close(fd[P2_READ]);
	close(fd[P2_WRITE]);

	// used for output
	pid = getpid();

	// send a value to the child
	printf("\nParent(%d): Sending %s to Child\n\n", pid, argv[1]);
	if(write(fd[P1_WRITE], argv[1], strlen(argv[1])) != strlen(argv[1])) {
		perror("Parent: Failed to send value to child");
		exit(EXIT_FAILURE);
	}
	// now wait for a response
	len = read(fd[P1_READ], &parent, strlen(parent));
	if(len < 0) {
		perror("Parent: Failed to read value from pipe");
		exit(EXIT_FAILURE);
	}
	else if(len == 0) {
		// not an error, but certainly unexpected
		fprintf(stderr, "Parent(%d): Read EOF from pipe", pid);
	} else {
		// report what we recieved
		printf("\nParent(%d): Recieved %s from Child\n\n", pid, parent);
	}
	// close down remaining descriptors
	close(fd[P1_READ]);
	close(fd[P1_WRITE]);

	// wait for child termination
	wait(NULL);

	return EXIT_SUCCESS;
}