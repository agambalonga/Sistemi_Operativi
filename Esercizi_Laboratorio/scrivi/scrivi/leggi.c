//Scrivere un programma C “leggi.c” che utilizzando la funzione primitiva “read”, legga il contenuto del file “alfabeto.txt” e lo stampi sullo standard output.i

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFDIM 2


int main(int argc, char* argv[]) {
	
	char buffer[BUFFDIM];
	int nRead;
	int offset=0;
	int fd = open("alfabeto.txt",O_RDONLY);

	if(fd == -1) {
		perror("open error");
		exit(-1);
	}

	while ( (nRead=read(fd,buffer,BUFFDIM)) > 0 ) {
		if(write(STDOUT_FILENO, buffer, nRead) == -1) {
			perror("write error");
			close(fd);
			exit(-2);
		}
		offset=offset+5;
		lseek(fd,offset,SEEK_SET);
	}
	
	close(fd);
	exit(0);
}
