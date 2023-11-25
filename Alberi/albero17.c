#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
int glob=5;
int pid = 0;
int main(){
	pid = fork();
	glob--;
	fork();
	pid=1;
	glob--;
	if (!pid){
		pid=fork();
		glob--;
	}
	if (pid!=0)
		printf("PADRE.  Glob: %d\n\n",glob);
	if (pid==0)
		printf("FIGLIO.  Glob: %d\n\n",glob);
}
