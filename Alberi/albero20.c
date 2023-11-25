#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
int glob=6;
int pid=1;
int i;
int main(){
	pid = fork();
	glob--;
	fork();
	pid=0;
	glob--;
	if (pid){
		pid=fork();
		glob--;
	}
	if (!pid){
		for (i=1;i<2;i++){
		pid = fork();
		glob++;
		}
	}
	if (pid!=0)
		printf("PADRE.  Glob: %d\n\n",glob);
	if (pid==0)
		printf("FIGLIO.  Glob: %d\n\n",glob);
}
