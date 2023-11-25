#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int glob = 4;
int pid = 0;

int main ()
{
	int i;
	for (i = 1; i < 4; i ++)
	{
		if (pid == 0)
		{
			pid = fork();
		}

		if (pid != 0)
		{
			glob = glob * 2;
		}

		glob = glob - 1;
	}

	printf ("Process %d glob = %d i = %d\n", getpid(), glob, i);
}
