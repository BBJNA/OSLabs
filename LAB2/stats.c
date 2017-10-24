#include <pthread.h>
#include <stdio.h>
#include <string.h>

void *Average(void *argv);
void *Max(void *argv);
void *Min(void *argv);

int length;

//Parent Process
int main(int argc, char *argv[]){

	length = argc;
	int i = 1;
	pthread_t tidAvg, tidMin, tidMax;
	pthread_attr_t attr;

	if (argc < 2)
	{		

		fprintf(stderr, "usage: stats <interger values>\n");
		return -1;

	}

	while(i<argc){

		if(atoi(argv[i])<0){

			fprintf(stderr, "%d must be >=0\n", atoi(argv[i]));

		}//end If
		i++;
	}//end While

	/* get the default attributes */
	pthread_attr_init(&attr);
	
	/* create the thread */
	pthread_create(&tidAvg,&attr,Average,(void *)argv);
	pthread_create(&tidMin,&attr,Min,(void *)argv);
	pthread_create(&tidMax,&attr,Max,(void *)argv);
	
	/* wait for the thread to exit */
	pthread_join(tidMin,NULL);
	pthread_join(tidAvg,NULL);
	pthread_join(tidMax,NULL);

	pthread_exit(NULL);


}

void *Average(void *argv){

	char **numbers = (char**)argv;

	double avg,sum=0;
	int i = 1;

	while(i < length){

		sum += atoi(numbers[i]);
		i++;
	}

	avg = sum/(length-1);

	printf("Average Value: %lf\n", avg);
	pthread_exit(NULL);
}

void *Max(void *argv){

	char **numbers = (char**)argv;

	int max = atoi(numbers[1]), i = 1;

	while(i < length){
		if (atoi(numbers[i])>max)
		{

			max = atoi(numbers[i]);

		}
		i++;
	}

	printf("Maximum Value: %d\n", max);
	pthread_exit(NULL);
}

void *Min(void *argv){

	char **numbers = (char**)argv;

	int min = atoi(numbers[1]), i = 1;


	while(i < length){
		if (atoi(numbers[i])<min)
		{

			min = atoi(numbers[i]);

		}
		i++;
	}

	printf("Minimum Value: %d\n", min);
	pthread_exit(NULL);
}