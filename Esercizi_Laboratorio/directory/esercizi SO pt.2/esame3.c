#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;

int *matrix;
int *matrix2;
int *array;

int m;
int done=0;
int column=0;

void *prod(void *arg);
void *print(void *arg);

int main(int argc,char** argv)
{

	if(argc!=2)
	{
		fprintf(stderr,"Bisogna immettere ./<Nome Programma> <Numero intero positivo m>\n");
		exit(-1);
	
	}
	
	m = atoi(argv[1]);
	
	if(m<=0)
	{
		fprintf(stderr,"Bisogna immettere un numero positivo maggiore di 0");
		exit(-1);
	}
	
	matrix = (int *)malloc(m*m*sizeof(int));
	matrix2 = (int *)malloc(m*m*sizeof(int));
	array = (int *)malloc(m*sizeof(int));
	
	srand(time(NULL));
	
	for(int i=0;i<m;i++)
		for(int j=0;j<m;j++)
			matrix[i*m+j]=rand()%101;
			
	for(int i=0;i<m;i++)
		for(int j=0;j<m;j++)
			matrix2[i*m+j]=rand()%101;
			
	pthread_t threads[m];
	int rc;
	
	for(int i=0;i<m;i++)
	{
		rc = pthread_create(&threads[i],NULL,prod,NULL);
		
		if(rc)
		{
			perror("pthread_create");
			exit(-1);
		}
	
	}
	
	rc = pthread_create(&threads[m],NULL,print,NULL);
	
	if(rc)
	{
		perror("pthread_create");
		exit(-1);
	}
	
	for(int i=0;i<=m;i++)
		pthread_join(threads[i],NULL);
	
	
	
	pthread_exit(NULL);
	
	free(matrix);
	free(matrix2);
	free(array);
	
	exit(0);

}

void *prod(void *arg)
{

	int sum=0;
	int prod=0;
	
	pthread_mutex_lock(&mutex);
	
	for(int i=0;i<m;i++)
	{
		prod=matrix[i*m+column]*matrix2[i*m+column];
		sum+=prod;
	}
	
	array[column]=sum;
	column++;
	
	pthread_mutex_unlock(&mutex);
	
	if(column==m)
	{
		pthread_mutex_lock(&mutex);
		done=1;
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
	
	for(int i=0;i<m;i++)
		printf("%d ",array[i]);
		
}

