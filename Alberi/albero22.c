#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
int glob=4;
int pid = 0;
int i;
int main(){
	pid = fork();
	pid=1;
	glob--;
	if (!pid){
		pid=fork();
		glob++;
	}
	pid=0;
	if (fork()){
		for (i=1;i<2;i++){
			pid = fork();
			glob++;
		}
	}
	if (pid!=0)
		printf("PADRE.  Glob: %d, i: %d\n\n",glob, i);
	if (pid==0)
		printf("FIGLIO.  Glob: %d, i: %d\n\n",glob, i);
}
