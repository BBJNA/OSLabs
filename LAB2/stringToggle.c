#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <errno.h>

int StringValid(char *string);
char *ToggleString(char string[]);

int main(int argc, char *argv[]){

	char ParentString[100], ChildString[100];
	int length, i;

	printf("Enter in a string: ");
	scanf("%s", ParentString);
	
	char test [strlen(ParentString)];
	strcpy(test, ToggleString(ParentString));

	printf("%s\n", test);

	int valid = StringValid(ParentString);

 	if(valid != 0){
	
	return -1;
	
	}

	int fd [4];
	pid_t pid;

	for(i=0;i<2;i++){

		if(pipe(fd+(i*2))<0){
			
			perror("Pipe wasn't created");
			exit(EXIT_FAILURE);			
			
		}
	}

	if((pid = fork())==-1){

		perror("fork");
		return 1;	

	}else{
	
		if(pid == 0){

			close(fd[0]);
			close(fd[3]);
			
			pid = getpid();

			length = read(fd[2], ChildString, strlen(ChildString));

			if(length < 0){

				perror("Pipe transfer failed");
				exit(EXIT_FAILURE);	

			}
			
			if(length == 0){

				perror("Something went wrong");


			}else{

				printf("\nChild got string\n");
				if(write(fd[1], ToggleString(ChildString), strlen(ChildString))<0){
				
					perror("Child did not write");
					exit(EXIT_FAILURE);	
		
				}
			
			}

			close(fd[2]);
			close(fd[1]);
			return (EXIT_SUCCESS);
			

		}else{

			close(fd[2]);
			close(fd[1]);

			pid = getpid();

			if(write(fd[3], ParentString, (strlen(ParentString))) != strlen(ParentString)){
			
				perror("Parent did not write properly");
				exit(EXIT_FAILURE);	

			}

			length = read(fd[0], ParentString, strlen(ParentString));
			printf("%d\n", length);

			if(length < 0){

					perror("Pipe transfer failed 2");
					exit(EXIT_FAILURE);			

				}
				
				if(length == 0){

					perror("Something went wrong 2");

				}else{

					printf("%s",ParentString);
				
				}

				close(fd[0]);
				close(fd[3]);
				wait(NULL);
				return (EXIT_SUCCESS);

		}
	}

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
	printf("%s\n",str);

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
