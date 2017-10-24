#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define MAX 1000

double randNum();
void *PointGen(void *argv);

int pointsInCircle = 0, totalPoints = 0;

//Parent Process
int main(int argc, char *argv[]){
	srand(time(NULL));
	int i = 1;
	pthread_t tid;
	pthread_attr_t attr;

	/* get the default attributes */
	pthread_attr_init(&attr);
	
	/* create the thread */
	pthread_create(&tid,&attr,PointGen,(void *)argv);

	/* wait for the thread to exit */
	pthread_join(tid,NULL);

	double pi = 4*(double)pointsInCircle/(double)totalPoints;

	printf("PI is estimated as: %lf with %d total and %d inside the circle.\n", pi, totalPoints, pointsInCircle);

	pthread_exit(NULL);


}

void *PointGen(void *argv){

	double x,y,M;
	totalPoints = rand()%MAX;

	for (int i = 0; i < totalPoints; i++)
	{

		x = randNum();
		y = randNum();
		M = sqrt(pow(x,2)+pow(y,2));
		printf("%lf %lf %lf\n", x,y,M);
		
		if (M<=1)
		{
			if (M>=-1)
			{
			
			pointsInCircle++;
			
			}

		}

	}

	pthread_exit(NULL);
}

double randNum(){
	
	int randomInt = rand() % MAX;
	double rnum = (double)(randomInt -(MAX/2))/(double)(MAX/2);
	return rnum;
}