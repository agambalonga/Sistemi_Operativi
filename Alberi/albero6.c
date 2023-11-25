#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int glob=0;
int main(){
	int i;
	int pid = 0;
	pid= fork();
	if (pid!=0){	
		glob++;
		pid=fork();
		glob--;
	}
	else if (pid==0){
		for (i=1;i<=2;i++){
			pid = fork();
			glob++;
		}
	}
	glob--;	
	printf("Sono il processo %d, figlio di %d. GLOB = %d i = %d\n",getpid(),getppid(), glob, i);
}
