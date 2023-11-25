#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
int glob=4;
int pid = 0;
int i=0;
int main(){
	fork();
	glob--;
	if (fork()){
		glob--;
	}
	if (pid==0){
		for (i=1;i<2;i++){
			pid = fork();
			glob++;
		}
	}
	if (pid==0)
		glob++;
	if (!fork())
		glob--;
	printf("Sono %d figlio di %d. Glob: %d, Pid: %d\n\n",getpid(),getppid(),glob, pid);
}
