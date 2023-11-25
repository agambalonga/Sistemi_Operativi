#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

int *matrix;
int *matrix2;
int *matrix3;

int k;
int m;
int p;

int k_cont = 0;
int done = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *prod(void *arg);
void *print(void *arg);

int main(int argc, char **argv)
{

	if(argc!=4)
	{
		fprintf(stderr,"Bisogna immettere ./<Nome Programma> <k numero intero positivo> <m numero intero positivo> <p numero intero positivo>\n");
		exit(-1);
	}
	
	
	k = atoi(argv[1]);
	m = atoi(argv[2]);
	p = atoi(argv[3]);
	
	matrix = (int *)malloc(k*m*sizeof(int));
	matrix2 = (int *)malloc(m*p*sizeof(int));
	matrix3 = (int *)malloc(k*p*sizeof(int));
	
	srand(time(NULL));
	
	for(int i=0;i<k;i++)
		for(int j=0;j<m;j++)
			matrix[i*k+j]=rand()%101;
			
	for(int i=0;i<m;i++)
		for(int j=0;j<p;j++)
			matrix2[i*m+j]=rand()%101;
			
	for(int i=0;i<k;i++)
		for(int j=0;j<p;j++)
			matrix3[i*k+j]=0;
			
	pthread_t threads[k];
	int rc;
	
	for(int i=0;i<k;i++)
	{
		rc = pthread_create(&threads[i],NULL,prod,NULL);
		
		if(rc)
		{
			perror("pthread_create");
			exit(-1);

		}
	
	}
	
	rc = pthread_create(&threads[k],NULL,print,NULL);
	
	if(rc)
	{
		perror("pthread_create");
		exit(-1);
	}
	
	for(int i=0;i<=k;i++)
		pthread_join(threads[i],NULL);
		
	pthread_exit(NULL);
	
	free(matrix);
	free(matrix2);
	free(matrix3);
	
	exit(0);


}

void *prod(void *arg)
{
	pthread_mutex_lock(&mutex);
	
	for(int i=0;i<k;i++)
		for(int j=0;j<m;j++)
			matrix3[i*k+j]+=matrix[j*k_cont+j]*matrix2[j*m+i];
			
	k_cont++;
			
	pthread_mutex_unlock(&mutex);
	
	if(k_cont==k)
	{
		pthread_mutex_lock(&mutex);
		done = 1;
		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&cond);
	}
			

}

void *print(void *arg)
{
	while(!done)
	{
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond,&mutex);
		pthread_mutex_unlock(&mutex);
	}
	
	for(int i=0;i<k;i++)
	{
		for(int j=0;j<p;j++)
		{
			printf("%d ",matrix3[i*k+j]);
		}
		
		printf("\n");
	}


}
