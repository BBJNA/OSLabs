#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_BUFFER 8196

int main(){

int max_length = 100; 
char srcFile[max_length], desFile[max_length];
ssize_t ret_in, ret_out;
char buffer[MAX_BUFFER];


printf("Enter in source file: ");
scanf("%s",srcFile);
//printf("%s\n",srcFile);

printf("Enter in destination: ");
scanf("%s",desFile);
//printf("%s\n",desFile);

int srcFD = open(srcFile,O_RDONLY);

if(srcFD == -1){
	perror("open");
	return 2;
}

int desFD = open(desFile,O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

if(desFD == -1){
	perror("open");
	return 3;
}


while((ret_in = read(srcFD, &buffer, MAX_BUFFER))){
	ret_out = write(desFD, &buffer, (ssize_t) ret_in);
	if(ret_out != ret_in){

		perror("write");
		return 4;

	}


}

close(srcFD);
close(desFD);

printf("Copying completed");

return (EXIT_SUCCESS);

}

