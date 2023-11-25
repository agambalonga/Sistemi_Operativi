#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <time.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int m;
int *matrix;
int *matrix2;
int *array;
int done = 0;
int cont_m=0;

void *prod(void *arg);
void *maxim(void *arg);

int main(int argc, char **argv)
{

	if(argc!=2)
	{
		fprintf(stderr,"Bisogna inserire ./<Nome Programma> <Dimensione Matrice>\n");
		exit(-1);
	}
	
	m = atoi(argv[1]);
	
	if(m<=1)
	{
		fprintf(stderr,"La dimensione della matrice deve essere maggiore di 1\n");
		exit(-1);
	}
	
	pthread_t threads[m+1];
	int rc;
	
	matrix =(int *)malloc(m*m*sizeof(int));
	matrix2 =(int *)malloc(m*m*sizeof(int));
	array =(int *)malloc(m*sizeof(int));
	
	
	srand(time(NULL));
	
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<m;j++)
		{
			matrix[i*m+j]=rand()%101;
		}
	}
	
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<m;j++)
		{
			matrix2[i*m+j]=rand()%101;
		}
	}
	
	for(int i=0;i<m;i++)
	{
		rc = pthread_create(&threads[i],NULL,prod,NULL);
		
		if(rc)
		{
			perror("thread");
			exit(-1);
		}
	}
	
	rc = pthread_create(&threads[m],NULL,maxim,NULL);
	
	if(rc)
	{
		perror("thread");
		exit(-1);
	}
	
	for(int i=0;i<m+1;i++)
		pthread_join(threads[i],NULL);
		
	
	
	printf("matrix");
	for(int i=0;i<m;i++)
	{
		printf("\n");
		for(int j=0;j<m;j++)
		{
			printf("%d ",matrix[i*m+j]);
		}
	}
	
	printf("\nmatrix2");
	for(int i=0;i<m;i++)
	{
		printf("\n");
		for(int j=0;j<m;j++)
		{
			printf("%d ",matrix2[i*m+j]);
		}
	}
	
	printf("\narray\n");
	for(int i=0;i<m;i++)
		printf("%d ",array[i]);
	
	free(matrix);
	free(matrix2);
	free(array);
	
	pthread_exit(NULL);
	
	exit(0);
	

}

void *prod(void *arg)
{
	int sum=0;
	int prod=0;
	
	pthread_mutex_lock(&mutex);
	for(int i=0;i<m;i++)
	{
		prod=matrix[i*m+cont_m]*matrix2[i*m+cont_m];
		sum=sum+prod;
	}
	array[cont_m]=sum;
	cont_m++;
	pthread_mutex_unlock(&mutex);
	
	if(cont_m==m)
	{
		pthread_mutex_lock(&mutex);
		done = 1;
		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&cond);
	}

}

void *maxim(void *arg)
{
	int max=0;
	
	while(!done)
	{
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond,&mutex);
		pthread_mutex_unlock(&mutex);
	}
	
	
	for(int i=0;i<m;i++)
	{
		if(max<array[i])
		max=array[i];
	
	}
	
	printf("The max is: %d\n",max);


}


