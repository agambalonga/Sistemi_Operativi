#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int glob = 5;
int pid = 0;

int main ()
{
	int i = 0;
	for (i = 1; i < 3; i ++)
	{
		pid = fork();
		if (pid == 0)
		{
			glob = glob * 2;
			sleep (i + 1);
		}
		
		glob = glob + 1;
	}

	printf ("Process %d, glob %d\n\n", getpid(), glob);

	exit (0);
}
