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
	glob--;
	fork();
	pid=4;
	glob--;
	if (!pid){
		pid=fork();
		glob--;
	}
	for (i=1;i<2;i++){
		pid = fork();
		glob++;
	}
	if (pid!=0)
		printf("PADRE.  Glob: %d\n\n",glob);
	if (pid==0)
		printf("FIGLIO.  Glob: %d\n\n",glob);
}
