#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int glob=4;
int pid=0;
int temp,i;
int main(){
	for (i=0;i<=2;i++){
		pid = fork();
		glob++;
	}
	if (glob>5){
		glob++;
		if (pid==0){
			pid=fork();
		}
		if (pid!=0){
			pid = fork();
			glob--;
		}
		if (pid==0){
			pid = fork();
			glob--;
		}
		if (pid!=0){
			temp=12;
			glob++;
			temp = glob;
			glob--;
		}
	}
	
	printf ("Process %d, glob = %d, temp = %d, i = %d\n", getpid(), glob, temp, i);
}

