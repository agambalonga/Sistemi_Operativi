#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
int glob=5;
int pid = 0;
int i=0;
int main(){
	fork();
	glob--;
	if (fork()){
		glob--;
	}
	if (pid==0){
		pid=fork();
		glob--;
	}
	for (i=0;i<2;i++){
		if (pid==0)
			pid = fork();
		if (pid!=0)
			glob--;
	}
	printf("Sono %d figlio di %d. Glob: %d\n\n",getpid(),getppid(),glob);
}
