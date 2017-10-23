#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>


#define P1_READ     0
#define P2_WRITE    1
#define P2_READ     2
#define P1_WRITE    3

int StringValid(char *string);
char *ToggleString(char string[]);

int main(int argc, char *argv[])
{
    int fd[4], length;
    pid_t pid;
    char ParentString[100], ChildString[100];

	printf("Enter in a string: ");
	scanf("%s", ParentString);
	
	int valid = StringValid(ParentString);

 	if(valid != 0){
	
    	exit(EXIT_FAILURE);
	
	}

        if (pipe(fd) < 0)
        {
            perror("Failed to allocate pipes");
            exit(EXIT_FAILURE);
        }

          if (pipe(fd+2) < 0)
        {
            perror("Failed to allocate pipes");
            exit(EXIT_FAILURE);
        }

    // fork() returns 0 for child process, child-pid for parent process.
    if ((pid = fork()) < 0)
    {
        perror("Failed to fork process");
        return EXIT_FAILURE;
    }

    // if the pid is zero, this is the child process
    if (pid == 0)
    {
        // Child. Start by closing descriptors we
        //  don't need in this process
        close(fd[P1_READ]);
        close(fd[P1_WRITE]);

        // used for output
        pid = getpid();

        // wait for parent to send us a value
        length = read(fd[P2_READ], &ChildString, sizeof(ChildString));
        if (length < 0)
        {
            perror("Child: Failed to read data from pipe");
            exit(EXIT_FAILURE);
        }
        else if (length == 0)
        {
            // not an error, but certainly unexpected
            fprintf(stderr, "Child: Read EOF from pipe");
        }
        else
  		{
  			strcpy(ChildString,ToggleString(ChildString));
            if (write(fd[P2_WRITE], &ChildString, sizeof(ChildString)) < 0)
            {
                perror("Child: Failed to write response value");
                exit(EXIT_FAILURE);
            }
        }

        // finished. close remaining descriptors.
        close(fd[P2_READ]);
        close(fd[P2_WRITE]);

        return EXIT_SUCCESS;
    }

    // Parent. close unneeded descriptors
    close(fd[P2_READ]);
    close(fd[P2_WRITE]);

    // used for output
    pid = getpid();

    // send a value to the child
    if (write(fd[P1_WRITE], &ParentString, sizeof(ParentString)) != sizeof(ParentString))
    {
        perror("Parent: Failed to send value to child ");
        exit(EXIT_FAILURE);
    }

    // now wait for a response
    length = read(fd[P1_READ], &ParentString, sizeof(ParentString));
    if (length < 0)
    {
        perror("Parent: failed to read value from pipe");
        exit(EXIT_FAILURE);
    }
    else if (length == 0)
    {
        // not an error, but certainly unexpected
        fprintf(stderr, "Parent(%d): Read EOF from pipe", pid);
    }
    else
    {
        // report what we received
        printf("Answer: %s\n", ParentString);
    }

    // close down remaining descriptors
    close(fd[P1_READ]);
    close(fd[P1_WRITE]);

    // wait for child termination
    wait(NULL);

    return EXIT_SUCCESS;
}

int StringValid(char *string){

	int i = 0;
	while(i<strlen(string)){
		if(!isalpha((int)string[i])){
			printf("\nUse only letters no numbers or special characters\n");
			return 1;
		}
		i++;

	}
	return 0;
}

char *ToggleString(char str[]){

	int i = 0;

	while(i<strlen(str)){
		
		if(str[i]>='A' && str[i]<='Z'){
			
			str[i] = str[i] + 32;

		}else{

			str[i] = str[i] - 32;
		}
		
		i++;

	}

	return str;
}
