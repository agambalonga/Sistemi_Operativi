#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>

#define SEM_EMPTY_NAME "/empty"
#define SEM_FULL_NAME "/full"
#define FIBO_FILENAME "fibonacci.txt"


struct {
	int n; //end sequence fibo
	sem_t* empty;
	sem_t* full;
	int fd; //file descriptor
	int count;
	pthread_mutex_t count_mutex;
	pthread_cond_t can_print;
}shared;


void *printer(void *arg) {
	
	pthread_mutex_lock(&shared.count_mutex);
	while(shared.count<shared.n) {
		pthread_cond_wait(&shared.can_print, &shared.count_mutex);
	}
	pthread_mutex_unlock(&shared.count_mutex);

	printf("OPERAZIONI CONCLUSE. ARRIVEDERCI DAL THREAD %lu\n", pthread_self());
	sleep(5);
		
	pthread_exit(NULL);
}

void *writer(void *arg) {
	int a=1, b=1;
	int fibo_number;
	
	
	
	for(int i=0; i<shared.n;i++) {
		sem_wait(shared.empty);
		lseek(shared.fd, 0, SEEK_SET);
		if(i<2){
			write(shared.fd, &a, sizeof(int));
			sem_post(shared.full);
		} else { 
			fibo_number = a+b;
			a = b;
			b = fibo_number;
			write(shared.fd, &fibo_number, sizeof(int));
			sem_post(shared.full);
		}
		usleep(500000);			
	}

	pthread_exit(NULL);
}


void *reader(void *arg) {
	int fibo_number;
	while(1) {
		sem_wait(shared.full);
		lseek(shared.fd, 0, SEEK_SET);
		read(shared.fd, &fibo_number, sizeof(int));
		printf("READER: Letto %d\n", fibo_number);
		sem_post(shared.empty);
		
		pthread_mutex_lock(&shared.count_mutex);
		shared.count++;
		if(shared.count == shared.n) {
			pthread_cond_signal(&shared.can_print);
			pthread_mutex_unlock(&shared.count_mutex);
			pthread_exit(NULL);
		}
		pthread_mutex_unlock(&shared.count_mutex);
	}

	pthread_exit(NULL);
}


int main(int argc, char* argv[]){
	if(argc!=2) {
		printf("Missing parameter");
		return -1;
	}
	
	sem_unlink(SEM_EMPTY_NAME);
	sem_unlink(SEM_FULL_NAME);

	shared.n = atoi(argv[1]);
	shared.count = 0;

	if(shared.n<10 || shared.n>30) {
		printf("Invalid parameter n");
		return -2;
	
	}
	
	shared.empty = sem_open(SEM_EMPTY_NAME, O_CREAT | O_EXCL, 0777, 1);
	shared.full = sem_open(SEM_FULL_NAME, O_CREAT | O_EXCL, 0777, 0);
	pthread_mutex_init(&shared.count_mutex, NULL);
	pthread_cond_init(&shared.can_print, NULL);
	
	shared.fd = open(FIBO_FILENAME, O_RDWR | O_CREAT | O_TRUNC, 0777);
	
	pthread_t th[3];
	pthread_create(&th[0], NULL, reader, NULL);
	pthread_create(&th[1], NULL, printer, NULL);
	pthread_create(&th[2], NULL, writer, NULL);

	for(int i=0; i<3; i++) {
		pthread_join(th[i], NULL);
	}

	
	close(shared.fd);
	pthread_mutex_destroy(&shared.count_mutex);
	pthread_cond_destroy(&shared.can_print);

	return 0;
}
